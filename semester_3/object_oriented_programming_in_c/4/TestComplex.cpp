#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <cstdio>
#include "Complex.h"

void testReadWriteAccess() {
    printf("Testing Read/Write Access...\n");
    Complex a(1.0, 2.0);
    
    a.real = 1.5;
    a.imag = 2.5;
    
    assert(a.real == 1.5);
    assert(a.imag == 2.5);
    assert(a == Complex(1.5, 2.5));
}

void testAmplitudeAndPhase() {
    printf("Testing Amplitude and Phase...\n");

    Complex a(1.5, 2.5);
    const Complex d(8.0, 15.0);

    assert(a.getAmplitude() == std::hypot(1.5, 2.5));
    assert(a.getPhase() == std::atan2(2.5, 1.5));
    
    assert(d.getAmplitude() == 17.0);
    assert(d.getPhase() == std::atan2(15.0, 8.0));
}

void testArithmeticOperators() {
    printf("Testing Arithmetic Operators...\n");
    Complex a(1.5, 2.5);
    Complex b(3.0, 4.0);

    assert(a + b == Complex(4.5, 6.5));
    assert(a - b == Complex(-1.5, -1.5));
    assert(a * b == Complex(-5.5, 13.5));
    assert(a / b == Complex(0.58, 0.06));
}

void testCompoundAssignment() {
    printf("Testing Compound Assignment...\n");
    Complex base(1.5, 2.5);
    Complex b(3.0, 4.0);
    Complex tempA;

    tempA = base;
    tempA += b;
    assert(tempA == Complex(4.5, 6.5));

    tempA = base;
    tempA -= b;
    assert(tempA == Complex(-1.5, -1.5));

    tempA = base;
    tempA *= b;
    assert(tempA == Complex(-5.5, 13.5));

    tempA = base;
    tempA /= b;
    assert(tempA == Complex(0.58, 0.06));
}

void testComparisonOperators() {
    printf("Testing Comparison Operators...\n");
    Complex a(1.5, 2.5);
    Complex b(3.0, 4.0);
    Complex aCopy(a);

    assert(a == aCopy);
    assert(!(a != aCopy));
    assert(a != b);
    assert(!(a == b));
}

void testChainingAndScalars() {
    printf("Testing Special Cases (Chaining & Scalars)...\n");
    
    Complex a, b, c;

    a = Complex(1.0, 2.0); b = Complex(3.0, 4.0); c = Complex(5.0, 6.0);
    a += b += c;
    assert(b == Complex(8.0, 10.0));
    assert(a == Complex(9.0, 12.0));

    a = Complex(1.0, 2.0); b = Complex(3.0, 4.0); c = Complex(5.0, 6.0);
    (a += b) += c;
    assert(a == Complex(9.0, 12.0));

    a = Complex(1.0, 2.0); b = Complex(3.0, 4.0); c = Complex(5.0, 6.0);
    a *= b *= c;
    assert(b == Complex(-9.0, 38.0));
    assert(a == Complex(-85.0, 20.0));

    a = Complex(1.0, 2.0); b = Complex(3.0, 4.0); c = Complex(5.0, 6.0);
    (a *= b) *= c;
    assert(a == Complex(-85.0, 20.0));

    a = Complex(1.0, 2.0);
    assert(a + 7 == Complex(8.0, 2.0));
    assert(7 + a == Complex(8.0, 2.0));

    b = Complex(3.0, 4.0);
    assert(b * 5 == Complex(15.0, 20.0));
    assert(5 * b == Complex(15.0, 20.0));

    c = Complex(3.5, 0.0);
    assert(c == 3.5);
    assert(3.5 == c);
    assert(c != 3.6);
    assert(3.6 != c);
}

int main() {
    printf("Running Complex class tests...\n");
    printf("--------------------------------\n");

    testReadWriteAccess();
    testAmplitudeAndPhase();
    testArithmeticOperators();
    testComparisonOperators();
    testCompoundAssignment();
    testChainingAndScalars();

    printf("--------------------------------\n");
    printf("All tests passed successfully!\n");

    return 0;
}