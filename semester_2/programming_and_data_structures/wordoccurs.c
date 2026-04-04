#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct ws {
    char *word;
    int count;
};

struct ws *words = NULL;   // dynamic array of word structures
size_t nwords = 0;         // number of words
size_t capacity = 0;       // allocated size

// Find word in the array (linear search)
struct ws *findword(char *word) {
    for (size_t i = 0; i < nwords; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return &words[i];
        }
    }
    return NULL;
}

// Read one word from file, return dynamically allocated string
char *getword(FILE *infile) {
    int c;
    size_t size = 0;
    size_t cap = 16;
    char *buf = malloc(cap);
    if (!buf) return NULL;

    while ((c = fgetc(infile)) != EOF && !isalpha(c))
        ;

    if (c == EOF) {
        free(buf);
        return NULL;
    }

    do {
        if (size + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[size++] = tolower(c);
        c = fgetc(infile);
    } while (c != EOF && isalpha(c));

    buf[size] = '\0';
    return buf;
}
    
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s infile\n", argv[0]);
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (!infile) {
        perror("fopen");
        return 1;
    }

    char *word;
    while ((word = getword(infile)) != NULL) {
        struct ws *entry = findword(word);
        if (entry) {
            entry->count++;
            free(word); // already in list
        } else {
            if (nwords == capacity) {
                capacity = capacity ? capacity * 2 : 8;
                struct ws *tmp = realloc(words, capacity * sizeof(struct ws));
                if (!tmp) {
                    perror("realloc");
                    free(word);
                    break;
                }
                words = tmp;
            }
            words[nwords].word = word;
            words[nwords].count = 1;
            nwords++;
        }
    }

    fclose(infile);

    // Print results
    for (size_t i = 0; i < nwords; i++) {
        printf("%s - %d\n", words[i].word, words[i].count);
    }

    // Free memory
    for (size_t i = 0; i < nwords; i++) {
        free(words[i].word);
    }
    free(words);

    return 0;
}
