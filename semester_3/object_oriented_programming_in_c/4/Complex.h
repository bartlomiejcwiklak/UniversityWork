#pragma once 

#include <iostream>

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0.0, double i = 0.0);

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    double getAmplitude() const;
    double getPhase() const;
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& os, const Complex& c);