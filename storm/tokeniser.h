#ifndef __TOKENISER_H__
#define __TOKENISER_H__

#include <stdio.h>

enum token_type_t {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_EQUAL,
    TOKEN_GREATERTHAN,
    TOKEN_LESSTHAN,
    TOKEN_INTEGER,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_OPEN_BRACE,
    TOKEN_CLOSE_BRACE,
    TOKEN_OPEN_SQUARE,
    TOKEN_CLOSE_SQUARE,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_ADDRESSOF,
    TOKEN_TILDE,
    TOKEN_PERCENT,
    TOKEN_EXCLAMATION
};

typedef struct {
    int line;
    int type;
    char token[1024];
    long integer;
} token_t;


token_t get_token(FILE *);
void tokenise(FILE *, token_t *, FILE *);


#endif
