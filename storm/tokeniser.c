#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokeniser.h"

static int get_token_line = 1;

token_t get_token(FILE *src) {
    size_t i = 0;
    int c;

    token_t token;

    while (isspace(c = fgetc(src))) {
        if (c == '\n')
            get_token_line++;
    }
    goto a;

    for (;;) {
        c = fgetc(src);
a:
        if (isspace(c))
            break;

        /* other tokens */
        switch (c) {
            case EOF:
                if (i) goto nospace;
                token.type = TOKEN_EOF;
                return token;
            case '>':
                if (i) goto nospace;
                token.type = TOKEN_GREATERTHAN;
                return token;
            case '<':
                if (i) goto nospace;
                token.type = TOKEN_LESSTHAN;
                return token;
            case '(':
                if (i) goto nospace;
                token.type = TOKEN_OPEN_BRACKET;
                return token;
            case ')':
                if (i) goto nospace;
                token.type = TOKEN_CLOSE_BRACKET;
                return token;
            case '{':
                if (i) goto nospace;
                token.type = TOKEN_OPEN_BRACE;
                return token;
            case '}':
                if (i) goto nospace;
                token.type = TOKEN_CLOSE_BRACE;
                return token;
            case ';':
                if (i) goto nospace;
                token.type = TOKEN_SEMICOLON;
                return token;
            case '+':
                if (i) goto nospace;
                token.type = TOKEN_ADD;
                return token;
            case '-':
                if (i) goto nospace;
                token.type = TOKEN_SUB;
                return token;
            case '*':
                if (i) goto nospace;
                token.type = TOKEN_MUL;
                return token;
            case '/':
                if (i) goto nospace;
                token.type = TOKEN_DIV;
                return token;
            case '=':
                if (i) goto nospace;
                token.type = TOKEN_EQUAL;
                return token;
            case ',':
                if (i) goto nospace;
                token.type = TOKEN_COMMA;
                return token;
            case '^':
                if (i) goto nospace;
                token.type = TOKEN_ADDRESSOF;
                return token;
            case '~':
                if (i) goto nospace;
                token.type = TOKEN_TILDE;
                return token;
            case '%':
                if (i) goto nospace;
                token.type = TOKEN_PERCENT;
                return token;
            nospace:
                ungetc(c, src);
                goto break2;
        }

        token.token[i++] = c;
    }

    if (c == '\n')
        get_token_line++;

break2:

    token.token[i] = 0;

    token.line = get_token_line;

    if (isdigit(token.token[0])) {
        token.type = TOKEN_INTEGER;
        token.integer = strtol(token.token, NULL, 0);
    } else {
        token.type = TOKEN_IDENTIFIER;
    }

    return token;
}

void tokenise(FILE *src, token_t *tokens, FILE *debug) {

    for (size_t i = 0; ; i++) {
        token_t token = get_token(src);

        tokens[i] = token;

        if (token.type == TOKEN_EOF) {
            fprintf(debug, "tokeniser: loaded %ld tokens\n", i);
            break;
        }

    }

    return;

}
