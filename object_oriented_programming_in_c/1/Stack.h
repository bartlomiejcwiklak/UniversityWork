#pragma once

#include <stdbool.h>

typedef struct {
    int* data;
    int top;
    int capacity;
    int errorCode;
} Stack;

void init(Stack *s);
void destroy(Stack *s);
void push(Stack *s, int element);
int pop(Stack *s);
bool isEmpty(const Stack *s);