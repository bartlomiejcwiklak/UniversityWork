#pragma once

#include <iostream>

class Stack {
    public:
        Stack(int initialCapacity = 4);

        ~Stack();

        void push(int element);
        int pop();
        bool isEmpty();

    private:
        int* data;
        int top;
        int capacity;
};