#include <stdio.h>
#include <stdlib.h>

#include "literals.h"
#include "tokeniser.h"
#include "lexer.h"
#include "codegen.h"

FILE *sourcefd;
FILE *outputasm;
FILE *tmp0;
FILE *tmp1;

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "No source specified.\n");
        abort();
    }

    if (!(sourcefd = fopen(argv[1], "rb"))) {
        perror("Couldn't open source file");
        abort();
    }


    if (!(outputasm = fopen(".mloutputasm", "wb"))) {
        perror("Couldn't open outputasm");
        abort();
    }


    if (!(tmp0 = fopen(".mltmp0", "wb"))) {
        perror("Couldn't open tmp0");
        abort();
    }

    literals_convert(sourcefd, outputasm, tmp0);

    fclose(sourcefd);
    fclose(tmp0);

    if (!(tmp0 = fopen(".mltmp0", "rb"))) {
        perror("Couldn't open tmp0");
        abort();
    }

    if (!(tmp1 = fopen(".mltmp1", "wb"))) {
        perror("Couldn't open tmp1");
        abort();
    }

    token_t *tokens = malloc(32768 * sizeof(token_t));

    tokenise(tmp0, tokens, stderr);

    lex_t *lexes = malloc(32768 * sizeof(lex_t));

    lex(lexes, tokens, stderr);

    codegen(outputasm, lexes);

    free(tokens);
    free(lexes);

    fclose(outputasm);
    fclose(tmp1);

    return 0;
}
