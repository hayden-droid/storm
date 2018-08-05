#include <stdio.h>
#include <stdlib.h>
#include "literals.h"
#include "machine.h"

void literals_convert(FILE *src, FILE *asmbl, FILE *next) {

    fprintf(asmbl, MACHINE_SECTION_DATA);

    int literal = 0;
    int in_escape = 0;
    int in_string = 0;

    for (;;) {
        int c = fgetc(src);

        if (in_escape) {
            switch (c) {
                case EOF:
                    fprintf(stderr, "error: EOF occurred while in string and parsing escape.\n");
                    abort();
                case '\n':
                    break;
                case 'n':
                    fprintf(asmbl, MACHINE_LITERAL_HEX, '\n');
                    break;
                case 'e':
                    fprintf(asmbl, MACHINE_LITERAL_HEX, '\e');
                    break;
                case '\\':
                    fprintf(asmbl, MACHINE_LITERAL_HEX, '\\');
                    break;
                default:
                    fprintf(asmbl, "\\%c", (char)c);
                    break;
            }
            in_escape = 0;
            continue;
        }

        switch (c) {
            case EOF:
                if (in_string) {
                    fprintf(stderr, "error: unmatched \" for string literal at EOF.\n");
                    abort();
                }
                return;
            case '"':
                if (!in_string) {
                    in_string = 1;
                    fprintf(asmbl, MACHINE_LITERAL_LABEL_BEGIN, literal);
                } else {
                    in_string = 0;
                    fprintf(asmbl, MACHINE_LITERAL_LABEL_END);
                    fprintf(next, "^__literal%d", literal++);
                }
                break;
            case '\\':
                if (in_string)
                    in_escape = 1;
                else
                    fputc(c, next);
                break;
            case '\n':
                if (in_string)
                    fprintf(asmbl, MACHINE_LITERAL_HEX, '\n');
                else
                    fputc(c, next);
                break;
            default:
                if (!in_string)
                    fputc(c, next);
                else
                    fputc(c, asmbl);
                break;
        }
    }
}
