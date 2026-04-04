#include "rand_malloc.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *str;
    struct Node *next;
} Node;

int main(void) {
    Node *head = NULL, *tail = NULL;
    char *line = NULL, *total = NULL, **arr = NULL;
    size_t count = 0;
    int mem_err = 0, fmt_err = 0;

    while (!mem_err) {
        size_t cap = 16, len = 0;
        line = rand_malloc(cap);
        if (!line) { mem_err = 1; break; }

        int c;
        while ((c = getchar()) != EOF && c != '\n') {
            if (len + 1 >= cap) {
                cap *= 2;
                char *tmp = rand_realloc(line, cap);
                if (!tmp) { free(line); line = NULL; mem_err = 1; break; }
                line = tmp;
            }
            line[len++] = (char)c;
        }
        if (mem_err) break;
        if (c == EOF && len == 0) {
            free(line);
            line = NULL;
            break;
        }
        line[len] = '\0';

        char *start = line;
        while (*start && isspace((unsigned char)*start)) start++;
        char *end = start + strlen(start);
        while (end > start && isspace((unsigned char)*(end-1))) end--;
        size_t slen = end - start;
        if (slen == 0) {
            free(line);
            line = NULL;
            continue;
        }

        for (size_t i = 0; i < slen; i++) {
            if (start[i] != '0' && start[i] != '1') {
                fmt_err = 1;
                free(line);
                line = NULL;
                mem_err = 1;  // to break out
                break;
            }
        }
        if (mem_err) break;

        char *bin = rand_malloc(slen + 1);
        if (!bin) { free(line); line = NULL; mem_err = 1; break; }
        memcpy(bin, start, slen);
        bin[slen] = '\0';
        free(line);
        line = NULL;

        Node *node = rand_malloc(sizeof *node);
        if (!node) { free(bin); mem_err = 1; break; }
        node->str = bin;
        node->next = NULL;
        if (!head) head = node;
        else tail->next = node;
        tail = node;
        count++;
    }

    if (!mem_err) {
        total = rand_malloc(2);
        if (!total) mem_err = 1;
        else strcpy(total, "0");
    }

    for (Node *cur = head; cur && !mem_err; cur = cur->next) {
        size_t ia = strlen(total), ib = strlen(cur->str), rl = 0;
        size_t cap = ia + ib + 2;
        char *rev = rand_malloc(cap);
        if (!rev) { mem_err = 1; break; }
        int carry = 0;
        while (ia || ib || carry) {
            int s = carry;
            if (ia) s += total[--ia] - '0';
            if (ib) s += cur->str[--ib] - '0';
            rev[rl++] = (s & 1) ? '1' : '0';
            carry = s >> 1;
        }
        while (rl > 1 && rev[rl-1] == '0') rl--;
        char *next = rand_malloc(rl + 1);
        if (!next) { free(rev); mem_err = 1; break; }
        for (size_t i = 0; i < rl; i++) next[i] = rev[rl-1-i];
        next[rl] = '\0';
        free(rev);
        free(total);
        total = next;
    }

    if (!mem_err && !fmt_err) {
        printf("Sum:\n%s\n\nInput numbers:\n", total);
 
        arr = rand_malloc(count * sizeof(char*));
        if (!arr) mem_err = 1;
        else {
            size_t i = 0;
            for (Node *cur = head; cur; cur = cur->next)
                arr[i++] = cur->str;
            for (size_t j = count; j > 0; j--)
                printf("%s\n", arr[j-1]);
        }
    }


    if (fmt_err)
        fprintf(stderr, "Error: invalid input format\n");
    else if (mem_err)
        fprintf(stderr, "Memory allocation failed\n");

    free(line);
    free(total);
    free(arr);
    for (Node *cur = head; cur; ) {
        Node *nx = cur->next;
        free(cur->str);
        free(cur);
        cur = nx;
    }

    return (fmt_err || mem_err) ? EXIT_FAILURE : EXIT_SUCCESS;
}
