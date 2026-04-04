#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4

void init(Stack *s) {
    s->data = (int*)malloc(sizeof(int) * INITIAL_CAPACITY);
    if (s->data == NULL) {
        fprintf(stderr, "! Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    s->top = 0;
    s->capacity = INITIAL_CAPACITY;
    s->errorCode = 0;
}

void destroy(Stack *s) {
    free(s->data);
    s->data = NULL;
    s->top = 0;
    s->capacity = 0;
}

bool isEmpty(const Stack *s) {
    return s->top == 0;
}

void push(Stack *s, int element) {
    if (s->top == s->capacity) {
        int newCapacity = s->capacity * 2;
        int* newData = (int*)realloc(s->data, sizeof(int) * newCapacity);

        if (newData == NULL) {
            fprintf(stderr, "! Memory allocation error\n");
            exit(EXIT_FAILURE);
        }

        s->data = newData;
        s->capacity = newCapacity;
    }
    s->data[s->top++] = element;
    s->errorCode = 0;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "! Stack is empty\n");
        s->errorCode = 1;
        return 0;
    }
    s->errorCode = 0;
    return s->data[--s->top];
}