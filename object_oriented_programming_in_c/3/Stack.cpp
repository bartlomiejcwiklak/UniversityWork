#include "Stack.h"
#include <iostream>
#include <stdlib.h>
#include <cstdio>

Stack::Stack(int initialCapacity) {
    capacity = initialCapacity > 0 ? initialCapacity : 4;
    data = (int*) malloc(capacity * sizeof(int));

    if (data == nullptr) {
        fprintf(stderr, "! Memory allocation error.\n");
        exit(1);
    }

    top = -1;
}

Stack::~Stack() {
    free(data);
}

Stack::Stack(const Stack& other) {
    top = other.top;
    int size = top + 1;

    capacity = (size > 0) ? size : 1;
    
    data = (int*) malloc(capacity * sizeof(int));
    if (data == nullptr) {
        fprintf(stderr, "! Memory allocation error in copy constructor.\n");
        exit(1);
    }

    for (int i = 0; i <= top; ++i) {
        data[i] = other.data[i];
    }
}

Stack& Stack::operator=(const Stack& other) {
    if (this == &other) {
        return *this;
    }

    int otherSize = other.top + 1;

    if (capacity < otherSize) {
        int newCapacity = (otherSize > 0) ? otherSize : 4;

        int* newData = (int*) realloc(data, newCapacity * sizeof(int));
        if (newData == nullptr) {
            fprintf(stderr, "! Memory allocation error in assignment operator.\n");
            exit(1);
        }
        data = newData;
        capacity = newCapacity;
    } 

    top = other.top;
    for (int i = 0; i <= top; ++i) {
        data[i] = other.data[i];
    }

    return *this;
}

bool Stack::isEmpty() {
    return top == -1;
}

void Stack::push(int element) {
    if (top >= capacity - 1) {
        int newCapacity = capacity * 2;
        int* newData = (int*) realloc(data, newCapacity * sizeof(int));

        if (newData == nullptr) {
            fprintf(stderr, "! Memory allocation error.\n");
            exit(1);
        }

        data = newData;
        capacity = newCapacity;
    }

    top++;
    data[top] = element;
}

bool Stack::pop(int& value) {
    if (isEmpty()) {
        fprintf(stderr, "! Stack is empty.\n");
        return false;
    }
    
    value = data[top--];
    return true;
}