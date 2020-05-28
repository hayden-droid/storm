#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdio.h>
#include "tokeniser.h"

typedef struct {
    char name[128];
    int type;
} variable_t;

typedef struct {
    int type;
    int precedence;
} operator_t;

typedef struct {
    char name[128];
    int type;
    variable_t args[128];
    size_t arg_count;
    variable_t locals[128];
    size_t local_count;
} function_t;

typedef struct {
    char name[128];
    int line;
    int type;
    union {
        operator_t operator;
        function_t function;
        variable_t variable;
    };
    long integer;
} lex_t;

enum lex_dtype_t {
    LEX_DTYPE_INT,
    LEX_DTYPE_GLOBAL,
    LEX_DTYPE_STATIC
};

enum lex_type_t {
    LEX_EOF,

    LEX_FUNCTION_DECLARATION,
    LEX_FUNCTION_END,
    LEX_FUNCTION_CALL,
    LEX_VARIABLE_DECLARATION,
    LEX_VARIABLE,
    LEX_INTEGER,
    LEX_COMMA,
    LEX_BLOCK_BEGIN,
    LEX_BLOCK_END,
    LEX_OPEN_BRACKET,
    LEX_CLOSE_BRACKET,
    LEX_SEMICOLON,
    LEX_ADDRESSOF,

    LEX_EXTERN,

    LEX_BREAK,

    LEX_ENDWHILE,
    LEX_WHILE,
    LEX_ENDIF,
    LEX_IF,
    LEX_RETURN,
    LEX_OPERATOR,

    LEX_ASSIGN,
    LEX_ISEQUAL,
    LEX_ADD,
    LEX_SUB,
    LEX_MUL,
    LEX_DIV,
    LEX_ISGREATER,
    LEX_ISLESS,
    LEX_ISGREATEROREQUAL,
    LEX_ISLESSOREQUAL,
    LEX_MODULO,

    LEX_STATEMENT_BEGIN,
    LEX_STATEMENT_END,
    LEX_EMPTY_STATEMENT
};

void lex(lex_t *, token_t *, FILE *);


#endif
