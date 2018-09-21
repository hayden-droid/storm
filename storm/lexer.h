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
    int arg_count;
    variable_t locals[128];
    int local_count;
} function_t;

typedef struct {
    char name[128];
    int line;
    int type;
    operator_t operator;
    function_t function;
    variable_t variable;
    long integer;
} lex_t;

#define LEX_DTYPE_INT 0
#define LEX_DTYPE_GLOBAL 1
#define LEX_DTYPE_STATIC 2

#define LEX_EOF                     0
#define LEX_FUNCTION_DECLARATION    10
#define LEX_FUNCTION_END            11
#define LEX_FUNCTION_CALL           20
#define LEX_VARIABLE_DECLARATION    30
#define LEX_VARIABLE                40
#define LEX_INTEGER                 50
#define LEX_COMMA                   60
#define LEX_BLOCK_BEGIN             100
#define LEX_BLOCK_END               110
#define LEX_OPEN_BRACKET            120
#define LEX_CLOSE_BRACKET           130
#define LEX_SEMICOLON               200
#define LEX_ADDRESSOF               500

#define LEX_EXTERN                  990

#define LEX_BREAK                   991

#define LEX_ENDWHILE                994
#define LEX_WHILE                   995
#define LEX_ENDIF                   996
#define LEX_IF                      997
#define LEX_RETURN                  998
#define LEX_OPERATOR                999

#define LEX_ASSIGN                  1000
#define LEX_ISEQUAL                 1001
#define LEX_ADD                     1002
#define LEX_SUB                     1003
#define LEX_MUL                     1004
#define LEX_DIV                     1005

#define LEX_INCREMENT               1006
#define LEX_DECREMENT               1007

#define LEX_STATEMENT_BEGIN         2000
#define LEX_STATEMENT_END           2001
#define LEX_SUBSTATEMENT_BEGIN      2002
#define LEX_SUBSTATEMENT_END        2003


void lex(lex_t *, token_t *, FILE *);


#endif
