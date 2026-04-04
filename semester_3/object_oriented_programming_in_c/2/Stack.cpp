#include "Stack.h"
#include <iostream>
#include <stdlib.h>
#include <climits>

Stack::Stack(int initialCapacity) {
    capacity = initialCapacity > 0 ? initialCapacity : 4;
    data = (int*) malloc(capacity * sizeof(int));

    if (data == nullptr) {
        fprintf(stderr, "! Memory allocation error.");
        exit(1);
    }

    top = -1;
}

Stack::~Stack() {
    free(data);
}

bool Stack::isEmpty() {
    return top == -1;
}

void Stack::push(int element) {
    if (top >= capacity - 1) {
        int newCapacity = capacity * 2;
        int* newData = (int*) realloc(data, newCapacity * sizeof(int));

        if (newData == nullptr) {
            fprintf(stderr, "! Memory allocation error.");
            exit(1);
        }

        data = newData;
        capacity = newCapacity;
    }

    top++;
    data[top] = element;
}

int Stack::pop() {
    if (isEmpty()) {
        fprintf(stderr, "! Stack is empty.\n");
        return INT_MIN;
    }
    return data[top--];
}