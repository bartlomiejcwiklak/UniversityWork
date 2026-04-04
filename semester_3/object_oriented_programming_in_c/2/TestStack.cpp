#include <iostream>
#include <assert.h>
#include "Stack.h"

void test_basic_operations();
void test_dynamic_growth();
void test_edge_cases();
void test_interleaved_operations();
void test_multiple_resizes();
void pop_while_empty();

int main() {
    printf("* Starting stack tests...\n");

    test_basic_operations();
    test_dynamic_growth();
    test_edge_cases();
    test_interleaved_operations();
    test_multiple_resizes();
    pop_while_empty();
    
    printf("\n* All stack tests passed successfully.\n");
    return 0;
}

void test_basic_operations() {
    printf("* Running test for basic operations...\n");
    Stack stack;
    assert(stack.isEmpty() == true);

    stack.push(10);
    stack.push(20);
    stack.push(30);
    assert(stack.isEmpty() == false);

    assert(stack.pop() == 30);
    assert(stack.pop() == 20);
    assert(stack.pop() == 10);

    assert(stack.isEmpty() == true);
    printf("...PASSED\n");
}

void test_dynamic_growth() {
    printf("* Running test for dynamic growth...\n");
    Stack stack;

    for (int i = 0; i < 10; ++i) {
        stack.push(i * 5);
    }

    for (int i = 9; i >= 0; --i) {
        assert(stack.pop() == i * 5);
    }

    assert(stack.isEmpty() == true);
    printf("...PASSED\n");
}

void test_edge_cases() {
    printf("* Running test for edge cases...\n");
    
    {
        Stack stack;
        stack.push(99);
        assert(stack.pop() == 99);
        assert(stack.isEmpty() == true);

        stack.push(-150);
        assert(stack.isEmpty() == false);
        assert(stack.pop() == -150);
    }
    {
        Stack stack;
        assert(stack.isEmpty() == true);
        stack.push(55);
        assert(stack.pop() == 55);
    }

    printf("...PASSED\n");
}

void test_interleaved_operations() {
    printf("* Running test for interleaved push/pop...\n");
    Stack stack;

    stack.push(10);
    stack.push(20);
    assert(stack.pop() == 20);

    stack.push(30);
    stack.push(40);
    assert(stack.pop() == 40);
    assert(stack.pop() == 30);

    assert(stack.isEmpty() == false);
    assert(stack.pop() == 10);
    assert(stack.isEmpty() == true);

    printf("...PASSED\n");
}

void test_multiple_resizes() {
    printf("* Running test for multiple resizes...\n");
    Stack stack;

    for (int i = 0; i < 10000; ++i) {
        stack.push(i);
    }

    for (int i = 9999; i >= 0; --i) {
        assert(stack.pop() == i);
    }

    assert(stack.isEmpty() == true);
    printf("...PASSED\n");
}

void pop_while_empty() {
    printf("* Running test for popping an empty stack...\n");
    Stack stack;

    stack.pop();
    printf("...PASSED\n");
}