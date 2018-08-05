#include <stdio.h>
#include "literals.h"
#include "machine.h"

void literals_convert(FILE *src, FILE *asmbl, FILE *next) {

    fprintf(asmbl, MACHINE_SECTION_DATA);

    int literal = 0;

    for (;;) {
        int c = fgetc(src);

        if (c == EOF)
            break;

        if (c == '"') {
            fprintf(asmbl, MACHINE_LITERAL_LABEL_BEGIN, literal);
            for (;;) {
                int c = fgetc(src);

                if (c == EOF)
                    return;

                if (c == '"') {
                    fprintf(asmbl, MACHINE_LITERAL_LABEL_END);
                    fprintf(next, "^__literal%d", literal++);
                    break;
                } else {
                    fputc(c, asmbl);
                }

            }
        } else {
            fputc(c, next);
        }
    }


}
