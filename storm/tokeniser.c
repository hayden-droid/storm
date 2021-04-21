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

    goto enter;
    for (;;) {
        c = fgetc(src);
enter:
        if (isspace(c))
            break;

        /* other tokens */
        switch (c) {
            #define TOKEN(C, T) \
                case C: \
                    if (i) goto nospace; \
                    token.type = T; \
                    return token

            TOKEN(EOF, TOKEN_EOF);
            TOKEN('>', TOKEN_GREATERTHAN);
            TOKEN('<', TOKEN_LESSTHAN);
            TOKEN('(', TOKEN_OPEN_BRACKET);
            TOKEN(')', TOKEN_CLOSE_BRACKET);
            TOKEN('{', TOKEN_OPEN_BRACE);
            TOKEN('}', TOKEN_CLOSE_BRACE);
            TOKEN(';', TOKEN_SEMICOLON);
            TOKEN('+', TOKEN_ADD);
            TOKEN('-', TOKEN_SUB);
            TOKEN('*', TOKEN_MUL);
            TOKEN('/', TOKEN_DIV);
            TOKEN('=', TOKEN_EQUAL);
            TOKEN(',', TOKEN_COMMA);
            TOKEN('^', TOKEN_ADDRESSOF);
            TOKEN('~', TOKEN_TILDE);
            TOKEN('%', TOKEN_PERCENT);
            TOKEN('!', TOKEN_EXCLAMATION);

            #undef TOKEN

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
}
