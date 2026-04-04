#include <iostream>
#include <assert.h>
#include <cstdio>
#include "Stack.h"

void testBasicOperations();
void testDynamicGrowth();
void testEdgeCases();
void testInterleavedOperations();
void testMultipleResizes();
void popWhileEmpty();

void testCopyFromNonEmpty();
void testCopyFromEmpty();
void testCopyInitialization();

void assignLargerToSmaller();
void assignSmallerToLarger();
void assignExactSameSize();
void assignWhenFirstStackIsEmpty();
void assignWhenSecondStackIsEmpty();
void assignStackToItself();

void executeBasicTests();
void executeCopyTests();
void executeAssignmentTests();

void gdbTest();

int main() {
    gdbTest();
    printf("* Starting Stack Tests...\n");
    executeBasicTests();
    
    printf("\n* Running Copy Constructor Tests...\n");
    executeCopyTests();

    printf("\n* Running Assignment Operator Tests...\n");
    executeAssignmentTests();
    
    printf("\n* All stack tests passed successfully.\n");
    return 0;
}

void testCopyFromNonEmpty() {
    printf("  - Running test: copy from non-empty...\n");
    int val;
    Stack s1; s1.push(10); s1.push(20); s1.push(30);
    
    Stack s2(s1);
    
    assert(s2.pop(val) && val == 30);
    assert(s2.pop(val) && val == 20);
    assert(s2.pop(val) && val == 10);
    assert(s2.isEmpty() == true);

    assert(s1.pop(val) && val == 30);
    assert(s1.pop(val) && val == 20);
    assert(s1.pop(val) && val == 10);
    assert(s1.isEmpty() == true);
    printf("  ...PASSED\n");
}

void testCopyFromEmpty() {
    printf("  - Running test: copy from empty...\n");
    int val;
    Stack sEmpty;
    Stack sNew(sEmpty);
    
    assert(sNew.isEmpty() == true);
    assert(sEmpty.isEmpty() == true);
    
    sNew.push(100);
    assert(sNew.pop(val) && val == 100);
    assert(sEmpty.isEmpty() == true);
    printf("  ...PASSED\n");
}

void testCopyInitialization() {
    printf("  - Running test: copy initialization (Stack s2 = s1)...\n");
    int val;
    Stack s1; s1.push(5); s1.push(15);
    
    Stack s2 = s1;
    
    assert(s2.pop(val) && val == 15);
    assert(s2.pop(val) && val == 5);
    assert(s1.pop(val) && val == 15);
    printf("  ...PASSED\n");
}

void assignLargerToSmaller() {
    printf("  - Running test: assign larger to smaller (s_small = s_large)...\n");
    int val;
    Stack sSmall; sSmall.push(1); sSmall.push(2);
    Stack sLarge; sLarge.push(100); sLarge.push(200); sLarge.push(300);
    
    sSmall = sLarge;
    
    assert(sSmall.pop(val) && val == 300);
    assert(sSmall.pop(val) && val == 200);
    assert(sSmall.pop(val) && val == 100);
    assert(sSmall.isEmpty() == true);
    assert(sLarge.pop(val) && val == 300);
    printf("  ...PASSED\n");
}

void assignSmallerToLarger() {
    printf("  - Running test: assign smaller to larger (s_large = s_small)...\n");
    int val;
    Stack sLarge; sLarge.push(1); sLarge.push(2); sLarge.push(3); sLarge.push(4); sLarge.push(5);
    Stack sSmall; sSmall.push(100); sSmall.push(200);
    
    sLarge = sSmall;
    
    assert(sLarge.pop(val) && val == 200);
    assert(sLarge.pop(val) && val == 100);
    assert(sLarge.isEmpty() == true);
    assert(sSmall.pop(val) && val == 200);
    printf("  ...PASSED\n");
}

void assignExactSameSize() {
    printf("  - Running test: assign same size (s1 = s2)...\n");
    int val;
    Stack s1; s1.push(1); s1.push(2);
    Stack s2; s2.push(3); s2.push(4);
    
    s1 = s2;
    
    assert(s1.pop(val) && val == 4);
    assert(s1.pop(val) && val == 3);
    assert(s1.isEmpty() == true);
    assert(s2.pop(val) && val == 4);
    printf("  ...PASSED\n");
}

void assignWhenFirstStackIsEmpty() {
    printf("  - Running test: assign to empty (s_empty = s_full)...\n");
    int val;
    Stack sEmpty;
    Stack sFull; sFull.push(55); sFull.push(66);
    
    sEmpty = sFull;
    
    assert(sEmpty.pop(val) && val == 66);
    assert(sEmpty.pop(val) && val == 55);
    assert(sFull.pop(val) && val == 66);
    printf("  ...PASSED\n");
}

void assignWhenSecondStackIsEmpty() {
    printf("  - Running test: assign from empty (s_full = s_empty)...\n");
    Stack sFull; sFull.push(77);
    Stack sEmpty;
    
    sFull = sEmpty;
    
    assert(sFull.isEmpty() == true);
    assert(sEmpty.isEmpty() == true);
    printf("  ...PASSED\n");
}

void assignStackToItself() {
    printf("  - Running test: self-assignment (s = s)...\n");
    int val;
    Stack s7; s7.push(10); s7.push(20);
    
    s7 = s7;
    
    assert(s7.pop(val) && val == 20);
    assert(s7.pop(val) && val == 10);
    assert(s7.isEmpty() == true);
    printf("  ...PASSED\n");
}

void testBasicOperations() {
    printf("  - Running test for basic operations...\n");
    Stack stack;
    int val;
    assert(stack.isEmpty() == true);

    stack.push(10);
    stack.push(20);
    stack.push(30);
    assert(stack.isEmpty() == false);

    assert(stack.pop(val) && val == 30);
    assert(stack.pop(val) && val == 20);
    assert(stack.pop(val) && val == 10);

    assert(stack.isEmpty() == true);
    printf("  ...PASSED\n");
}

void testDynamicGrowth() {
    printf("  - Running test for dynamic growth...\n");
    Stack stack;
    int val;

    for (int i = 0; i < 10; ++i) {
        stack.push(i * 5);
    }

    for (int i = 9; i >= 0; --i) {
        assert(stack.pop(val) && val == i * 5);
    }

    assert(stack.isEmpty() == true);
    printf("  ...PASSED\n");
}

void testEdgeCases() {
    printf("  - Running test for edge cases...\n");
    int val;
    
    {
        Stack stack;
        stack.push(99);
        assert(stack.pop(val) && val == 99);
        assert(stack.isEmpty() == true);

        stack.push(-150);
        assert(stack.isEmpty() == false);
        assert(stack.pop(val) && val == -150);
    }
    {
        Stack stack;
        assert(stack.isEmpty() == true);
        stack.push(55);
        assert(stack.pop(val) && val == 55);
    }

    printf("  ...PASSED\n");
}

void testInterleavedOperations() {
    printf("  - Running test for interleaved push/pop...\n");
    Stack stack;
    int val;

    stack.push(10);
    stack.push(20);
    assert(stack.pop(val) && val == 20);

    stack.push(30);
    stack.push(40);
    assert(stack.pop(val) && val == 40);
    assert(stack.pop(val) && val == 30);

    assert(stack.isEmpty() == false);
    assert(stack.pop(val) && val == 10);
    assert(stack.isEmpty() == true);

    printf("  ...PASSED\n");
}

void testMultipleResizes() {
    printf("  - Running test for multiple resizes...\n");
    Stack stack;
    int val;

    for (int i = 0; i < 10000; ++i) {
        stack.push(i);  
    }

    for (int i = 9999; i >= 0; --i) {
        assert(stack.pop(val) && val == i);
    }

    assert(stack.isEmpty() == true);
    printf("  ...PASSED\n");
}

void popWhileEmpty() {
    printf("  - Running test for popping an empty stack...\n");
    Stack stack;
    int val;

    bool success = stack.pop(val);
    assert(success == false);
    
    printf("  ...PASSED\n");
}

void gdbTest() {
    Stack s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack s2(s1);
    Stack s3 = s1;
    Stack s4;
    s4.push(10);
    s4 = s1;
}

void executeBasicTests() {
    testBasicOperations();
    testDynamicGrowth();
    testEdgeCases();
    testInterleavedOperations();
    testMultipleResizes();
    popWhileEmpty();
}

void executeCopyTests() {
    testCopyFromNonEmpty();
    testCopyFromEmpty();
    testCopyInitialization();
}

void executeAssignmentTests() {
    assignLargerToSmaller();
    assignSmallerToLarger();
    assignExactSameSize();
    assignWhenFirstStackIsEmpty();
    assignWhenSecondStackIsEmpty();
    assignStackToItself();
}