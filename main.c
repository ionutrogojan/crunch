#include <stdio.h>

#include "lib/lexer.h"

int main(int argc, char **argv) {
    // 0 = ./main , 1 = source , count = 2
    if (argc < 2) {
        printf("No input file specified\n");
        return 1;
    } else if (argc > 2) {
        printf("Too many input files specified\n");
        return 1;
    }
    const char *src = argv[1];

    // This might require a realpath when it becomes an environment call
    FILE *fp = fopen(src, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    Buffer fb = { .index = 0 };

    while ((fb.length = fread(fb.data, 1, BUFFER_SIZE, fp)) > 0)
        tokenizeBuffer(&fb);

    fclose(fp);
    return 0;
}
