#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct words {
    char *word;
    int count;
};

char *readLine(FILE *fp){
    int c;
    size_t len = 0;
    size_t size = 16;
    char *buffer = malloc(size);
    if (!buffer){
        fprintf(stderr, "Error allocating memory!");
        exit(1);
    }

    while ((c = fgetc(fp)) != EOF && c != '\n'){
        if (len + 1 >= size){
            size *= 2;
            char *tmp = realloc(buffer, size);
            if (!tmp) {
                fprintf(stderr, "Error allocating memory!");
                exit(1);
            }
            buffer = tmp;
        }
        buffer[len++] = (char)c;
    }

    if (len == 0 && c == EOF){
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Incorrect amount of arguments!");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp){
        fprintf(stderr, "Error opening the file!");
        return 1;
    }

    char *line;
    while ((line = readLine(fp)) != NULL){
        char *token = strtok(line, " \t");
        int first = 1;

        while (token != NULL) {
                
        }
    }


}