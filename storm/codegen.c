#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "codegen.h"
#include "machine.h"


static int in_function = 0;
static function_t *current_function;


static variable_t global_vars[1024];
static size_t global_vars_count = 0;


/* returns 0 for local variables, 1 for global variables, -1 for not found */
/* variable_t *variable returns the variable type */
/* ssize_t *offset returns the offset onto the stack (locals only) */
/* char *name is the name of the variable */
/* function_t *function is the current function */
static int variable_resolve(variable_t *variable, ssize_t *offset, char *name, function_t *function) {

    /* search local variables */
    for (size_t i = 0; i < function->local_count; i++) {
        if (!strcmp(function->locals[i].name, name)) {
            *variable = function->locals[i];
            *offset = -((i + 1) * MACHINE_STACK_ELEMENT_SIZE);
            return 0;
        }
    }

    /* search arguments */
    for (size_t i = 0; i < function->arg_count; i++) {
        if (!strcmp(function->args[i].name, name)) {
            *variable = function->args[i];
            *offset = ((function->arg_count - 1) - i) * MACHINE_STACK_ELEMENT_SIZE +
                        MACHINE_STACK_ELEMENT_SIZE * 2;
            return 0;
        }
    }

    /* search globals */
    for (size_t i = 0; i < global_vars_count; i++) {
        if (!strcmp(global_vars[i].name, name)) {
            *variable = global_vars[i];
            *offset = 0;
            return 1;
        }
    }

    return -1;
}

static void new_function(FILE *output) {

    fprintf(output, MACHINE_SECTION_TEXT);

    if (current_function->type == LEX_DTYPE_GLOBAL)
        fprintf(output, MACHINE_GLOBAL_REF, current_function->name);

    fprintf(output, MACHINE_NEW_LABEL, current_function->name);

    fprintf(output, MACHINE_CREATE_FRAME);

    if (current_function->local_count)
        fprintf(output, MACHINE_ALLOCATE_STACK, current_function->local_count * MACHINE_STACK_ELEMENT_SIZE);

    return;
}

static void new_global_var(FILE *output, variable_t var) {

    fprintf(output, MACHINE_SECTION_DATA);

    if (var.type == LEX_DTYPE_GLOBAL)
        fprintf(output, MACHINE_GLOBAL_REF, var.name);

    global_vars[global_vars_count] = var;

    global_vars_count++;

    fprintf(output, MACHINE_GLOBAL_VAR, var.name);

    return;
}

static void put_operator(FILE *output, operator_t op) {

    switch (op.type) {
        case LEX_ADD:
            fprintf(output, MACHINE_ADD);
            break;
        case LEX_SUB:
            fprintf(output, MACHINE_SUB);
            break;
        case LEX_MUL:
            fprintf(output, MACHINE_MUL);
            break;
        case LEX_DIV:
            fprintf(output, MACHINE_DIV);
            break;
        case LEX_MODULO:
            fprintf(output, MACHINE_MODULO);
            break;
        case LEX_ISEQUAL:
            fprintf(output, MACHINE_ISEQUAL);
            break;
        case LEX_ISABOVE:
            fprintf(output, MACHINE_ISABOVE);
            break;
        case LEX_ISBELOW:
            fprintf(output, MACHINE_ISBELOW);
            break;
    }

    return;
}


static lex_t operator_stack[1024];
static int op_stack_ptr = 0;

static int function_arg_depth[1024];
static int fn_arg_ptr = 0;

static int cdecl_defined = 0;

static void statement_compile(FILE *output, lex_t *lexes) {

    variable_t var;
    ssize_t offset;

    int is_assignment = 0;
    ssize_t assignee_off;
    char *assignee_name;
    int assignee_isglobal;
    variable_t assignee;

    if (lexes[1].type == LEX_ASSIGN) {
        is_assignment = 1;
        assignee_isglobal = variable_resolve(&assignee, &assignee_off, lexes[0].name, current_function);
        assignee_name = lexes[0].name;
        lexes += 2;
    }

    for (size_t i = 0; ; i++) {
        switch (lexes[i].type) {
            case LEX_COMMA:
                function_arg_depth[fn_arg_ptr]++;
                while (operator_stack[op_stack_ptr].type != LEX_OPEN_BRACKET) {
                    put_operator(output, operator_stack[op_stack_ptr--].operator);
                }
                break;
            case LEX_STATEMENT_END:
                while (op_stack_ptr) {
                    if (operator_stack[op_stack_ptr].type == LEX_OPERATOR)
                        put_operator(output, operator_stack[op_stack_ptr--].operator);
                }
                if (is_assignment) {
                    if (assignee_isglobal) {
                        fprintf(output, MACHINE_ASSIGN_GLOBAL, assignee_name);
                    } else {
                        fprintf(output, MACHINE_ASSIGN_LOCAL, (int)assignee_off);
                    }
                } else {
                    fprintf(output, MACHINE_POP_RESULT);
                }
                return;
            case LEX_INTEGER:
                fprintf(output, MACHINE_PUSH_INTEGER, lexes[i].integer);
                break;
            case LEX_VARIABLE:
                if (variable_resolve(&var, &offset, lexes[i].name, current_function)) {
                    fprintf(output, MACHINE_PUSH_GLOBAL, lexes[i].name);
                } else {
                    fprintf(output, MACHINE_PUSH_LOCAL, (int)offset);
                }
                break;
            case LEX_FUNCTION_CALL:
                fn_arg_ptr++;
                if (lexes[i+2].type == LEX_CLOSE_BRACKET)
                    function_arg_depth[fn_arg_ptr] = 0;
                else
                    function_arg_depth[fn_arg_ptr] = 1;
                /* FALLTHRU */
            case LEX_OPEN_BRACKET:
                operator_stack[++op_stack_ptr] = lexes[i];
                break;
            case LEX_CLOSE_BRACKET:
                while (operator_stack[op_stack_ptr].type != LEX_OPEN_BRACKET) {
                    if (op_stack_ptr < 1) {
                        fprintf(stderr, "panic\n");
                        abort();
                    }
                    put_operator(output, operator_stack[op_stack_ptr--].operator);
                }
                op_stack_ptr--;
                if (operator_stack[op_stack_ptr].type == LEX_FUNCTION_CALL) {
                    if (!strcmp(operator_stack[op_stack_ptr].name, "poke8")) {
                        fprintf(output, MACHINE_POKE8);
                    } else if (!strcmp(operator_stack[op_stack_ptr].name, "poke16")) {
                        fprintf(output, MACHINE_POKE16);
                    } else if (!strcmp(operator_stack[op_stack_ptr].name, "poke32")) {
                        fprintf(output, MACHINE_POKE32);
                    } else if (!strcmp(operator_stack[op_stack_ptr].name, "poke64")) {
                        fprintf(output, MACHINE_POKE64);
                    } else if (!strcmp(operator_stack[op_stack_ptr].name, "peek8")) {
                        fprintf(output, MACHINE_PEEK8);
                    } else if (!strcmp(operator_stack[op_stack_ptr].name, "peek16")) {
                        fprintf(output, MACHINE_PEEK16);
                    } else if (!strcmp(operator_stack[op_stack_ptr].name, "peek32")) {
                        fprintf(output, MACHINE_PEEK32);
                    } else if (!strcmp(operator_stack[op_stack_ptr].name, "peek64")) {
                        fprintf(output, MACHINE_PEEK64);
                    } else {
                        if (!strcmp(operator_stack[op_stack_ptr].name, "cdecl"))
                            cdecl_defined = 1;
                        fprintf(output, MACHINE_FUNCTION_CALL, operator_stack[op_stack_ptr].name, function_arg_depth[fn_arg_ptr] * MACHINE_STACK_ELEMENT_SIZE);
                    }
                    op_stack_ptr--;
                    fn_arg_ptr--;
                }
                break;
            case LEX_ADDRESSOF:
                if (variable_resolve(&var, &offset, lexes[i].name, current_function)) {
                    fprintf(output, MACHINE_PUSH_ADDROF_GLOBAL, lexes[i].name);
                } else {
                    fprintf(output, MACHINE_PUSH_ADDROF_LOCAL, (int)offset);
                }
                break;
            case LEX_OPERATOR:
                while (operator_stack[op_stack_ptr].type == LEX_OPERATOR
                       && lexes[i].operator.precedence <= operator_stack[op_stack_ptr].operator.precedence) {
                    put_operator(output, operator_stack[op_stack_ptr--].operator);
                }
                operator_stack[++op_stack_ptr] = lexes[i];
                break;
        }
    }

}

static int labels = 0;

typedef struct {
    int type;
    int label;
    int labelstart;
} keyword_t;

#define KEYWORD_IF      1000
#define KEYWORD_WHILE   2000

static keyword_t keywords[1024];
static size_t keywords_ptr = 0;

void codegen(FILE *output, lex_t *lexes) {

    int ret = 0;

    for (size_t i = 0; ; i++) {
        switch (lexes[i].type) {
            case LEX_EOF:
                if (cdecl_defined) {
                    fprintf(output, MACHINE_SECTION_TEXT);
                    fprintf(output, MACHINE_CDECL);
                }
                return;
            case LEX_EXTERN:
                fprintf(output, MACHINE_EXTERN_REF, lexes[i].name);
                break;
            case LEX_FUNCTION_DECLARATION:
                current_function = &lexes[i].function;
                new_function(output);
                in_function = 1;
                break;
            case LEX_FUNCTION_END:
                fprintf(output, MACHINE_RETURNZERO);
                in_function = 0;
                break;
            case LEX_VARIABLE_DECLARATION:
                new_global_var(output, lexes[i].variable);
                break;
            case LEX_STATEMENT_BEGIN:
                statement_compile(output, &lexes[i+1]);
                if (ret) {
                    fprintf(output, MACHINE_RETURN);
                    ret = 0;
                }
                break;
            case LEX_IF:
                i++;
                statement_compile(output, &lexes[i+1]);
                keywords[keywords_ptr].type = KEYWORD_IF;
                keywords[keywords_ptr++].label = labels;
                fprintf(output, MACHINE_IF, labels++);
                break;
            case LEX_ENDIF:
                fprintf(output, MACHINE_INTLABEL, keywords[--keywords_ptr].label);
                break;
            case LEX_BREAK:
                {
                int kw;
                for (kw = keywords_ptr;
                     keywords[kw].type != KEYWORD_WHILE;
                     kw--);
                fprintf(output, MACHINE_ENDWHILE, keywords[kw].label);
                }
                break;
            case LEX_WHILE:
                i++;
                keywords[keywords_ptr].type = KEYWORD_WHILE;
                keywords[keywords_ptr].labelstart = labels++;
                keywords[keywords_ptr].label = labels++;
                fprintf(output, MACHINE_INTLABEL, keywords[keywords_ptr].labelstart);
                statement_compile(output, &lexes[i+1]);
                fprintf(output, MACHINE_WHILE, keywords[keywords_ptr++].label);
                break;
            case LEX_ENDWHILE:
                fprintf(output, MACHINE_ENDWHILE, keywords[--keywords_ptr].labelstart);
                fprintf(output, MACHINE_INTLABEL, keywords[keywords_ptr].label);
                break;
            case LEX_RETURN:
                ret = 1;
                break;
        }
    }

}
