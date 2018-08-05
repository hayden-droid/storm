#include <stdio.h>
#include <stdlib.h>

#include "literals.h"
#include "tokeniser.h"
#include "lexer.h"
#include "codegen.h"

FILE *sourcefd;
FILE *outputasm;
FILE *tmp0;

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "No source specified.\n");
        abort();
    }

    if (argc < 3) {
        fprintf(stderr, "No output name specified.\n");
        abort();
    }

    if (!(sourcefd = fopen(argv[1], "rb"))) {
        perror("Couldn't open source file");
        abort();
    }

    if (!(outputasm = fopen(argv[2], "wb"))) {
        fclose(sourcefd);
        perror("Couldn't open output file");
        abort();
    }

    if (!(tmp0 = tmpfile())) {
        fclose(sourcefd);
        fclose(outputasm);
        perror("Couldn't open tmp0");
        abort();
    }

    literals_convert(sourcefd, outputasm, tmp0);

    fclose(sourcefd);

    rewind(tmp0);

    token_t *tokens = malloc(32768 * sizeof(token_t));

    tokenise(tmp0, tokens, stderr);

    lex_t *lexes = malloc(32768 * sizeof(lex_t));

    lex(lexes, tokens, stderr);

    codegen(outputasm, lexes);

    free(tokens);
    free(lexes);

    fclose(outputasm);
    fclose(tmp0);

    return 0;
}
