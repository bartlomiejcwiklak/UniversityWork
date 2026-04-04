#pragma once

#include <iostream>
#include <map>

class Poly {
private:
    std::map<int, double> coefficients;

public:
    Poly(double constantVal = 0.0);
    
    ~Poly();

    double& operator[](int exponent);
    double operator[](int exponent) const;

    double operator()(double x) const;

    friend Poly operator+(const Poly& lhs, const Poly& rhs);
    friend Poly operator-(const Poly& lhs, const Poly& rhs);
    friend Poly operator*(const Poly& lhs, const Poly& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Poly& poly);
};