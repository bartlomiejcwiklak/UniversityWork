#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getWord(FILE *fp){
    int c;
    size_t size = 0;
    size_t cap = 16;

    char *buf = malloc(cap);

    if (!buf){
        return NULL;
    }

    while ((c = fgetc(fp)) != EOF && !isspace(c))
        ;

    if (c == EOF) {
        free(buf);
        return NULL;
    }

    do {
        if (size + 1 >= buf){
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[size++] = tolower(c);
        c = fgetc(fp);
    } while (c != EOF && isalpha(c));

    buf[size] = '\0';
    return buf;
}