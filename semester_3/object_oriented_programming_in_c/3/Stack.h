#pragma once

class Stack {
    public:
        Stack(int initialCapacity = 4);
        ~Stack();

        Stack(const Stack& other);
        Stack& operator=(const Stack& other);

        void push(int element);
        bool pop(int& value);
        bool isEmpty();

    private:
        int* data;
        int top;
        int capacity;
};