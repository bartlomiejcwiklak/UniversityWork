#include "Stack.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void test_basic_operations();
void test_edge_cases();
void test_interleaved_operations();
void test_multiple_resizes();
void test_three_stacks();
void pop_while_empty();

int main() {
    printf("* Starting stack tests...\n");

    test_basic_operations();
    test_edge_cases();
    test_interleaved_operations();
    test_multiple_resizes();
    test_three_stacks();
    pop_while_empty();

    printf("\n* All stack tests passed successfully.\n");
    return 0;
}

void test_basic_operations() {
    printf("* Running test for basic operations...\n");
    Stack s;
    init(&s);
    assert(isEmpty(&s) == true);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    assert(isEmpty(&s) == false);

    assert(pop(&s) == 30);
    assert(pop(&s) == 20);
    assert(pop(&s) == 10);

    assert(isEmpty(&s) == true);

    destroy(&s);
    printf("...PASSED\n");
}

void test_edge_cases() {
    printf("* Running test for edge cases...\n");
    Stack s;
    init(&s);

    push(&s, 99);
    assert(pop(&s) == 99);
    assert(isEmpty(&s) == true);

    push(&s, -150);
    assert(isEmpty(&s) == false);
    assert(pop(&s) == -150);

    destroy(&s);
    init(&s);
    assert(isEmpty(&s) == true);
    push(&s, 55);
    assert(pop(&s) == 55);

    destroy(&s);
    printf("...PASSED\n");
}

void test_interleaved_operations() {
    printf("* Running test for interleaved push/pop...\n");
    Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    assert(pop(&s) == 20);

    push(&s, 30);
    push(&s, 40);
    assert(pop(&s) == 40);
    assert(pop(&s) == 30);

    assert(isEmpty(&s) == false);
    assert(pop(&s) == 10);
    assert(isEmpty(&s) == true);

    destroy(&s);
    printf("...PASSED\n");
}

void test_multiple_resizes() {
    printf("* Running test for multiple resizes...\n");
    Stack s;
    init(&s);

    for (int i = 0; i < 10000; ++i) {
        push(&s, i);
    }

    for (int i = 9999; i >= 0; --i) {
        assert(pop(&s) == i);
    }

    assert(isEmpty(&s) == true);
    destroy(&s);
    printf("...PASSED\n");
}

void pop_while_empty() {
    printf("* Running test for popping an empty stack...\n");
    Stack s;
    init(&s);
    pop(&s);
    assert(s.errorCode != 0);
    destroy(&s);
    printf("...PASSED\n");
}

void test_three_stacks() {
    printf("* Running test for three concurrent stacks...\n");
    Stack s1, s2, s3;
    init(&s1);
    init(&s2);
    init(&s3);

    assert(isEmpty(&s1) == true);
    assert(isEmpty(&s2) == true);
    assert(isEmpty(&s3) == true);

    push(&s1, 100);
    push(&s2, 200);
    push(&s3, 300);
    push(&s1, 101);

    assert(isEmpty(&s1) == false);
    assert(isEmpty(&s2) == false);
    assert(isEmpty(&s3) == false);

    assert(pop(&s1) == 101);
    push(&s2, 201);
    push(&s3, 301);

    assert(pop(&s2) == 201); 
    assert(pop(&s3) == 301); 
    assert(pop(&s1) == 100);

    assert(isEmpty(&s1) == true);
    assert(isEmpty(&s2) == false);
    assert(isEmpty(&s3) == false);

    assert(pop(&s2) == 200);
    assert(pop(&s3) == 300);

    assert(isEmpty(&s1) == true);
    assert(isEmpty(&s2) == true);
    assert(isEmpty(&s3) == true);

    destroy(&s1);
    destroy(&s2);
    destroy(&s3);

    printf("...PASSED\n");
}