#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

void testConstructorsAndAccess() {
    std::cout << "Testing Constructors and Access...\n";
    Matrix m1(3, 4);
    assert(m1.getRows() == 3);
    assert(m1.getCols() == 4);

    m1(0, 0) = 1.1;
    m1(2, 3) = 9.9;

    assert(m1(0, 0) == 1.1);
    assert(m1(2, 3) == 9.9);

    const Matrix m2 = m1;
    assert(m2(0, 0) == 1.1);
}

void testReferenceCounting() {
    std::cout << "Testing Reference Counting...\n";
    Matrix m1(2, 2);
    m1(0, 0) = 1.0;
    m1(0, 1) = 2.0;
    m1(1, 0) = 3.0;
    m1(1, 1) = 4.0;

    Matrix m2 = m1;
    Matrix m3(1, 1);
    m3 = m1;

    assert(m1(1, 1) == 4.0);
    assert(m2(1, 1) == 4.0);
    assert(m3(1, 1) == 4.0);
    
    m2(1, 1) = 44.0;

    assert(m1(1, 1) == 4.0);
    assert(m2(1, 1) == 44.0);
    assert(m3(1, 1) == 4.0);

    m3(0, 1) = 22.0;

    assert(m1(0, 1) == 2.0);
    assert(m2(0, 1) == 2.0);
    assert(m3(0, 1) == 22.0);
    
    m1 = m1;
    assert(m1(1, 1) == 4.0);
}

void testProxyLogic() {
    std::cout << "Testing Proxy Logic...\n";
    Matrix m(2, 2);
    m(0, 0) = 10.0;
    m(0, 1) = 20.0;

    m(0, 0) += 5.0;
    assert(m(0, 0) == 15.0);

    m(0, 0) -= 5.0;
    assert(m(0, 0) == 10.0);
    
    m(0, 0) *= 2.0;
    assert(m(0, 0) == 20.0);

    m(0, 0) /= 2.0;
    assert(m(0, 0) == 10.0);

    m(0, 0) = m(0, 1); 
    assert(m(0, 0) == 20.0);

    double x = m(0, 1);
    assert(x == 20.0);
    
    const Matrix cm = m;
    double y = cm(0, 0);
    
    assert(y == 20.0);
}

void testArithmetic() {
    std::cout << "Testing Arithmetic Operators...\n";
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(0, 0) = 1; a(0, 1) = 2; a(1, 0) = 3; a(1, 1) = 4;
    b(0, 0) = 5; b(0, 1) = 6; b(1, 0) = 7; b(1, 1) = 8;

    Matrix c = a + b;
    assert(c(0, 0) == 6 && c(0, 1) == 8 && c(1, 0) == 10 && c(1, 1) == 12);

    Matrix d = a - b;
    assert(d(0, 0) == -4 && d(0, 1) == -4 && d(1, 0) == -4 && d(1, 1) == -4);

    a += b;
    assert(a(0, 0) == 6 && a(0, 1) == 8 && a(1, 0) == 10 && a(1, 1) == 12);

    a -= b;
    assert(a(0, 0) == 1 && a(0, 1) == 2 && a(1, 0) == 3 && a(1, 1) == 4);

    Matrix m1(2, 3);
    m1(0, 0) = 1; m1(0, 1) = 2; m1(0, 2) = 3;
    m1(1, 0) = 4; m1(1, 1) = 5; m1(1, 2) = 6;

    Matrix m2(3, 2);
    m2(0, 0) = 7; m2(0, 1) = 8;
    m2(1, 0) = 9; m2(1, 1) = 10;
    m2(2, 0) = 11; m2(2, 1) = 12;

    Matrix m3 = m1 * m2;
    assert(m3.getRows() == 2 && m3.getCols() == 2);
    assert(m3(0, 0) == 58);
    assert(m3(0, 1) == 64);
    assert(m3(1, 0) == 139);
    assert(m3(1, 1) == 154);
    
    m1 *= m2;
    assert(m1(0, 0) == 58);
    assert(m1(1, 1) == 154);
}

void testComparison() {
    std::cout << "Testing Comparison Operators...\n";
    Matrix a(2, 2);
    a(0, 0) = 1; a(0, 1) = 2; a(1, 0) = 3; a(1, 1) = 4;
    
    Matrix b = a;
    assert(a == b);
    
    Matrix c(2, 2);
    c(0, 0) = 1; c(0, 1) = 2; c(1, 0) = 3; c(1, 1) = 4;
    assert(a == c);

    b(1, 1) = 44.0;
    assert(a != b);
    
    Matrix d(3, 3);
    assert(a != d);
}

void testStreamIO() {
    std::cout << "Testing Stream I/O...\n";
    Matrix m(2, 3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4.5; m(1, 1) = 5.5; m(1, 2) = 6.5;

    std::stringstream ss;
    ss << m;
    assert(ss.str() == "1 2 3 \n4.5 5.5 6.5 \n");

    std::ofstream outFile("matrix.txt");
    outFile << "2 2\n11 22\n33 44\n";
    outFile.close();

    Matrix mRead;
    std::ifstream inFile("matrix.txt");
    assert(mRead.getRows() == 1 && mRead.getCols() == 1);
    
    inFile >> mRead;
    inFile.close();
    
    assert(mRead.getRows() == 2);
    assert(mRead.getCols() == 2);
    assert(mRead(0, 0) == 11);
    assert(mRead(1, 1) == 44);
}

void testExceptions() {
    std::cout << "Testing Exceptions...\n";
    Matrix m(3, 3);
    Matrix mBad(4, 4);

    bool caught = false;
    try {
        double x = m(5, 5);
        (void)x;
    } catch (const MatrixIndexOutOfBounds& e) {
        caught = true;
    }
    assert(caught);

    caught = false;
    try {
        m(5, 5) = 10;
    } catch (const MatrixIndexOutOfBounds& e) {
        caught = true;
    }
    assert(caught);

    caught = false;
    try {
        Matrix mSum = m + mBad;
    } catch (const MatrixDimensionMismatch& e) {
        caught = true;
    }
    assert(caught);

    caught = false;
    try {
        Matrix mProd = m * mBad;
    } catch (const MatrixDimensionMismatch& e) {
        caught = true;
    }
    assert(caught);
    
    caught = false;
    try {
        std::stringstream badStream("2 2\n1 2 3");
        badStream >> m;
    } catch (const MatrixReadError& e) {
        caught = true;
    }
    assert(caught);
}

void testIncrementOperators() {
    std::cout << "Testing Increment Operators...\n";
    
    Matrix m(1, 1);
    m(0, 0) = 5.0;

    double preResult = ++m(0, 0); 
    assert(m(0, 0) == 6.0);
    assert(preResult == 6.0);

    double postResult = m(0, 0)++;
    assert(m(0, 0) == 7.0);
    assert(postResult == 6.0);
    
    Matrix m1(1, 1);
    m1(0, 0) = 10.0;
    Matrix m2 = m1; 
    
    m2(0, 0)++;
    
    assert(m1(0, 0) == 10.0);
    assert(m2(0, 0) == 11.0);

    Matrix m3 = m2;
    ++m3(0, 0);

    assert(m2(0, 0) == 11.0);
    assert(m3(0, 0) == 12.0);
}

int main() {
    try {
        testConstructorsAndAccess();
        testReferenceCounting();
        testProxyLogic();
        testIncrementOperators();
        testArithmetic();
        testComparison();
        testStreamIO();
        testExceptions();

        std::cout << "\nAll tests passed successfully!\n";
    } catch (const MatrixException& e) {
        std::cerr << "An unexpected exception occurred: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "An unknown error occurred.\n";
        return 1;
    }

    return 0;
}