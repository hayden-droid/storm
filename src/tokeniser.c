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
                token.type = TOKEN_DEREFERENCE;
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

        switch (token.type) {
            case TOKEN_EOF:
                fprintf(debug, "line %d: token_eof\n", token.line);
                break;
            case TOKEN_INTEGER:
                fprintf(debug, "line %d: token_integer, value: %ld\n", token.line, token.integer);
                break;
            case TOKEN_OPEN_BRACKET:
                fprintf(debug, "line %d: token_open_bracket\n", token.line);
                break;
            case TOKEN_CLOSE_BRACKET:
                fprintf(debug, "line %d: token_close_bracket\n", token.line);
                break;
            case TOKEN_OPEN_BRACE:
                fprintf(debug, "line %d: token_open_brace\n", token.line);
                break;
            case TOKEN_CLOSE_BRACE:
                fprintf(debug, "line %d: token_close_brace\n", token.line);
                break;
            case TOKEN_SEMICOLON:
                fprintf(debug, "line %d: token_semicolon\n", token.line);
                break;
            case TOKEN_ADD:
                fprintf(debug, "line %d: token_add\n", token.line);
                break;
            case TOKEN_SUB:
                fprintf(debug, "line %d: token_sub\n", token.line);
                break;
            case TOKEN_MUL:
                fprintf(debug, "line %d: token_mul\n", token.line);
                break;
            case TOKEN_DIV:
                fprintf(debug, "line %d: token_div\n", token.line);
                break;
            case TOKEN_EQUAL:
                fprintf(debug, "line %d: token_equal\n", token.line);
                break;
            case TOKEN_COMMA:
                fprintf(debug, "line %d: token_comma\n", token.line);
                break;
            case TOKEN_ADDRESSOF:
                fprintf(debug, "line %d: token_addressof\n", token.line);
                break;
            case TOKEN_DEREFERENCE:
                fprintf(debug, "line %d: token_dereference\n", token.line);
                break;
            case TOKEN_IDENTIFIER:
                fprintf(debug, "line %d: token_identifier, value: %s\n", token.line, token.token);
                break;
        }

        tokens[i] = token;

        if (token.type == TOKEN_EOF) {
            fprintf(debug, "loaded %d tokens\n", i);
            break;
        }

    }

    return;

}
