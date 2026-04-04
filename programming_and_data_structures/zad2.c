#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int charDetection(const char *line, char a, char b) {
    for (int i = 0; line[i+1] != '\0'; i++){
        if (line[i] == a && line[i+1] == b){
            return 1;
        }
    }
    return 0;
}

void reverseWord(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

char *readLine(FILE *fp) {
    int c;
    size_t size = 16;
    size_t len = 0;
    char *buffer = malloc(size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed!");
        exit(1);
    }

    while((c = fgetc(fp)) != EOF && c != '\n') {
        if (len + 1 >= size){
            size *= 2;
            char *tmp = realloc(buffer, size);
            if (!tmp) {
                fprintf(stderr, "Memory allocation failed!");
                exit(1);
            }
            buffer = tmp;
        }
        buffer[len++] = (char)c;
    }

    if (len == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc != 3){
        fprintf(stderr, "Incorrect amount of arguments.");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp){
        fprintf(stderr, "Error opening the file.");
        return 1;
    }

    FILE *fp2 = fopen(argv[2], "w");
    if (!fp2){
        fprintf(stderr, "Error opening the file.");
        return 1;
    }

    char *line;
    while ((line = readLine(fp)) != NULL) {
        char *token = strtok(line, " \t");
        int first = 1;

        while (token != NULL) {
            if (charDetection(token, 'h', 'e')){
                reverseWord(token);
            }

            if (!first){
                fprintf(fp2, " ");
            }
            fprintf(fp2, "%s", token);

            first = 0;
            token = strtok(NULL, " \t");
        }
        fprintf(fp2, "\n");

        free(line);
    }

    fclose(fp2);
    fclose(fp);
    return 0;
}