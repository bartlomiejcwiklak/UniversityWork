#include "Complex.h"
#include <cmath>

Complex::Complex(double r, double i) : real(r), imag(i) {}

Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    real -= other.real;
    imag -= other.imag;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    double oldReal = real;
    real = oldReal * other.real - imag * other.imag;
    imag = oldReal * other.imag + imag * other.real;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double denominator = other.real * other.real + other.imag * other.imag;
    double oldReal = real;
    real = (oldReal * other.real + imag * other.imag) / denominator;
    imag = (imag * other.real - oldReal * other.imag) / denominator;
    return *this;
}

double Complex::getAmplitude() const {
    return std::hypot(real, imag);
}

double Complex::getPhase() const {
    return std::atan2(imag, real);
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
    Complex temp = lhs;
    temp += rhs;
    return temp;
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
    Complex temp = lhs;
    temp -= rhs;
    return temp;
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
    Complex temp = lhs;
    temp *= rhs;
    return temp;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    Complex temp = lhs;
    temp /= rhs;
    return temp;
}

bool operator==(const Complex& lhs, const Complex& rhs) {
    return (lhs.real == rhs.real) && (lhs.imag == rhs.imag);
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << ", " << c.imag << "i)";
    return os;
}