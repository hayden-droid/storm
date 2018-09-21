#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "tokeniser.h"
#include "lexer.h"
#include "machine.h"

#define TYPES_COUNT 3
static char *types[TYPES_COUNT] = {
    "var", "global", "static"
};

static int is_statement = 0;
static int in_function = 0;
static function_t *current_function;

void lex(lex_t *lexes, token_t *tokens, FILE *debug) {
    size_t cur_lex = 0;

    for (size_t i = 0; ; i++, cur_lex++) {
        switch (tokens[i].type) {
            case TOKEN_EOF:
                fprintf(debug, "lex: token eof\n");
                lexes[cur_lex].type = LEX_EOF;
                return;
            case TOKEN_INTEGER:
                if (!is_statement) {
                    is_statement = 1;
                    lexes[cur_lex].type = LEX_STATEMENT_BEGIN;
                    cur_lex++;
                    fprintf(debug, "lex: statement begin\n");
                }
                fprintf(debug, "lex: integer %d\n", tokens[i].integer);
                lexes[cur_lex].type = LEX_INTEGER;
                lexes[cur_lex].integer = tokens[i].integer;
                break;
            case TOKEN_OPEN_BRACE:
                fprintf(debug, "lex: block begin\n");
                lexes[cur_lex].type = LEX_BLOCK_BEGIN;
                break;
            case TOKEN_CLOSE_BRACE:
                fprintf(debug, "lex: block end\n");
                lexes[cur_lex].type = LEX_BLOCK_END;
                break;
            case TOKEN_OPEN_BRACKET:
                if (!is_statement) {
                    is_statement = 1;
                    lexes[cur_lex].type = LEX_STATEMENT_BEGIN;
                    cur_lex++;
                    fprintf(debug, "lex: statement begin\n");
                }
                fprintf(debug, "lex: open bracket\n");
                lexes[cur_lex].type = LEX_OPEN_BRACKET;
                break;
            case TOKEN_CLOSE_BRACKET:
                fprintf(debug, "lex: close bracket\n");
                lexes[cur_lex].type = LEX_CLOSE_BRACKET;
                break;
            case TOKEN_SEMICOLON:
                is_statement = 0;
                fprintf(debug, "lex: statement end\n");
                lexes[cur_lex].type = LEX_STATEMENT_END;
                break;
            case TOKEN_ADD:
                fprintf(debug, "lex: add\n");
                lexes[cur_lex].type = LEX_OPERATOR;
                lexes[cur_lex].operator.type = LEX_ADD;
                lexes[cur_lex].operator.precedence = 1000;
                break;
            case TOKEN_SUB:
                fprintf(debug, "lex: sub\n");
                lexes[cur_lex].type = LEX_OPERATOR;
                lexes[cur_lex].operator.type = LEX_SUB;
                lexes[cur_lex].operator.precedence = 1000;
                break;
            case TOKEN_MUL:
                fprintf(debug, "lex: mul\n");
                lexes[cur_lex].type = LEX_OPERATOR;
                lexes[cur_lex].operator.type = LEX_MUL;
                lexes[cur_lex].operator.precedence = 2000;
                break;
            case TOKEN_DIV:
                fprintf(debug, "lex: div\n");
                lexes[cur_lex].type = LEX_OPERATOR;
                lexes[cur_lex].operator.type = LEX_DIV;
                lexes[cur_lex].operator.precedence = 2000;
                break;
            case TOKEN_COMMA:
                fprintf(debug, "lex: comma\n");
                lexes[cur_lex].type = LEX_COMMA;
                break;
            case TOKEN_EQUAL:
                if (tokens[i+1].type == TOKEN_EQUAL) {
                    i++;
                    lexes[cur_lex].type = LEX_OPERATOR;
                    lexes[cur_lex].operator.type = LEX_ISEQUAL;
                    lexes[cur_lex].operator.precedence = 500;
                    fprintf(debug, "lex: isequal\n");
                } else {
                    fprintf(debug, "lex: assign\n");
                    lexes[cur_lex].type = LEX_ASSIGN;
                }
                break;
            case TOKEN_GREATERTHAN:
                fprintf(debug, "lex: isabove\n");
                lexes[cur_lex].type = LEX_OPERATOR;
                lexes[cur_lex].operator.type = LEX_ISABOVE;
                lexes[cur_lex].operator.precedence = 500;
                break;
            case TOKEN_LESSTHAN:
                fprintf(debug, "lex: isbelow\n");
                lexes[cur_lex].type = LEX_OPERATOR;
                lexes[cur_lex].operator.type = LEX_ISBELOW;
                lexes[cur_lex].operator.precedence = 500;
                break;
            case TOKEN_ADDRESSOF:
                if (!is_statement) {
                    is_statement = 1;
                    lexes[cur_lex].type = LEX_STATEMENT_BEGIN;
                    cur_lex++;
                    fprintf(debug, "lex: statement begin\n");
                }
                lexes[cur_lex].type = LEX_ADDRESSOF;
                strcpy(lexes[cur_lex].name, tokens[++i].token);
                fprintf(debug, "lex: address of %s\n", lexes[cur_lex].name);
                break;
            case TOKEN_IDENTIFIER:
                /* check for types */
                for (size_t j = 0; j < TYPES_COUNT; j++) {
                    if (!strcmp(tokens[i].token, types[j])) {
                        /* check if function */
                        size_t is_function;
                        for (is_function = 0; tokens[i+1+is_function].type == TOKEN_MUL; is_function++);
                        if (tokens[i+2+is_function].type == TOKEN_OPEN_BRACKET) {
                            /*** function declaration ***/
                            lexes[cur_lex].type = LEX_FUNCTION_DECLARATION;
                            lexes[cur_lex].function.type = j;
                            i++;
                            strcpy(lexes[cur_lex].function.name, tokens[i].token);
                            i += 2;
                            lexes[cur_lex].function.arg_count = 0;
                            lexes[cur_lex].function.local_count = 0;
                            fprintf(debug, "lex: function declaration: name = %s, type = %s\n",
                                    lexes[cur_lex].function.name,
                                    types[lexes[cur_lex].function.type]);
                            fprintf(debug, "lex: arguments:\n");
                            size_t jj;
                            for (jj = 0; tokens[i].type != TOKEN_CLOSE_BRACKET; i++, jj++) {
                                if (tokens[i].type == TOKEN_COMMA)
                                    i++;
                                for (size_t j = 0; j < TYPES_COUNT; j++) {
                                    if (!strcmp(tokens[i].token, types[j])) {
                                        lexes[cur_lex].function.args[jj].type = j;
                                    }
                                }
                                i++;
                                strcpy(lexes[cur_lex].function.args[jj].name, tokens[i].token);
                                fprintf(debug, "lex: argument declaration: name = %s, type = %s\n",
                                        lexes[cur_lex].function.args[jj].name,
                                        types[lexes[cur_lex].function.args[jj].type]);
                            }
                            lexes[cur_lex].function.arg_count = jj;
                            fprintf(debug, "lex: end of declaration, arg count = %d\n", jj);
                            in_function = 1;
                            current_function = &lexes[cur_lex].function;
                        } else {
                            /*** variable declaration ***/
                            if (in_function) {
                                /*** local variable declaration ***/
                                current_function->locals[current_function->local_count].type = j;
                                i++;
                                strcpy(current_function->locals[current_function->local_count].name, tokens[i].token);
                                fprintf(debug, "lex: local variable declaration: name = %s, type = %s\n",
                                        current_function->locals[current_function->local_count].name,
                                        types[current_function->locals[current_function->local_count].type]);
                                current_function->local_count++;
                                cur_lex--;
                            } else {
                                /*** global variable declaration ***/
                                lexes[cur_lex].type = LEX_VARIABLE_DECLARATION;
                                lexes[cur_lex].variable.type = j;
                                i++;
                                strcpy(lexes[cur_lex].variable.name, tokens[i].token);
                                fprintf(debug, "lex: global variable declaration: name = %s, type = %s\n",
                                        lexes[cur_lex].variable.name,
                                        types[lexes[cur_lex].variable.type]);
                            }
                            if (tokens[++i].type != TOKEN_SEMICOLON) {
                                fprintf(stderr, "line %d: error: expected ';'\n", tokens[i].line);
                                abort();
                            }
                        }
                        goto continue2;
                    }

                }

                if (!strcmp(tokens[i].token, "endfun")) {
                    in_function = 0;
                    fprintf(debug, "lex: function end\n");
                    lexes[cur_lex].type = LEX_FUNCTION_END;
                    goto continue2;
                }

                if (!strcmp(tokens[i].token, "return")) {
                    fprintf(debug, "lex: return\n");
                    lexes[cur_lex].type = LEX_RETURN;
                    goto continue2;
                }

                if (!strcmp(tokens[i].token, "if")) {
                    fprintf(debug, "lex: if\n");
                    lexes[cur_lex].type = LEX_IF;
                    goto continue2;
                }

                if (!strcmp(tokens[i].token, "endif")) {
                    fprintf(debug, "lex: endif\n");
                    lexes[cur_lex].type = LEX_ENDIF;
                    goto continue2;
                }

                if (!strcmp(tokens[i].token, "break")) {
                    fprintf(debug, "lex: break\n");
                    lexes[cur_lex].type = LEX_BREAK;
                    goto continue2;
                }

                if (!strcmp(tokens[i].token, "while")) {
                    fprintf(debug, "lex: while\n");
                    lexes[cur_lex].type = LEX_WHILE;
                    goto continue2;
                }

                if (!strcmp(tokens[i].token, "endwhile")) {
                    fprintf(debug, "lex: endwhile\n");
                    lexes[cur_lex].type = LEX_ENDWHILE;
                    goto continue2;
                }

                if (!strcmp(tokens[i].token, "extern")) {
                    fprintf(debug, "lex: extern\n");
                    lexes[cur_lex].type = LEX_EXTERN;
                    strcpy(lexes[cur_lex].name, tokens[i+1].token);
                    i += 2;
                    goto continue2;
                }

                /* it's a normal statement */
                if (!is_statement) {
                    is_statement = 1;
                    lexes[cur_lex].type = LEX_STATEMENT_BEGIN;
                    cur_lex++;
                    fprintf(debug, "lex: statement begin\n");
                }

                if (tokens[i+1].type == TOKEN_OPEN_BRACKET) {
                    lexes[cur_lex].type = LEX_FUNCTION_CALL;
                    strcpy(lexes[cur_lex].name, tokens[i].token);
                    fprintf(debug, "lex: function call: %s\n", lexes[cur_lex].name);
                    goto continue2;
                }
                lexes[cur_lex].type = LEX_VARIABLE;
                strcpy(lexes[cur_lex].name, tokens[i].token);
                fprintf(debug, "lex: variable: %s\n", lexes[cur_lex].name);
                goto continue2;
        }
        continue2:
        ;
    }

}
