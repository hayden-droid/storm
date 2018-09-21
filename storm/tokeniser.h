#ifndef __TOKENISER_H__
#define __TOKENISER_H__

#include <stdio.h>

#define TOKEN_EOF 0
#define TOKEN_IDENTIFIER    100
#define TOKEN_ADD  1
#define TOKEN_SUB  2
#define TOKEN_MUL  3
#define TOKEN_DIV  4
#define TOKEN_EQUAL 5
#define TOKEN_GREATERTHAN 6
#define TOKEN_LESSTHAN 7
#define TOKEN_INTEGER 10
#define TOKEN_OPEN_BRACKET  20
#define TOKEN_CLOSE_BRACKET 21
#define TOKEN_OPEN_BRACE  22
#define TOKEN_CLOSE_BRACE  23
#define TOKEN_OPEN_SQUARE  24
#define TOKEN_CLOSE_SQUARE  25
#define TOKEN_SEMICOLON     40
#define TOKEN_COMMA     41
#define TOKEN_ADDRESSOF     60
#define TOKEN_DEREFERENCE   61


typedef struct {
    int line;
    int type;
    char token[1024];    
    long integer;
} token_t;


token_t get_token(FILE *);
void tokenise(FILE *, token_t *, FILE *);


#endif
