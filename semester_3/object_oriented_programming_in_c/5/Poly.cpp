#include "Poly.h"
#include <cmath>
#include <algorithm>

Poly::Poly(double constantVal) {
    if (constantVal != 0.0) {
        coefficients[0] = constantVal;
    }
}

Poly::~Poly() {
}

double& Poly::operator[](int exponent) {
    return coefficients[exponent];
}

double Poly::operator[](int exponent) const {
    auto it = coefficients.find(exponent);
    if (it != coefficients.end()) {
        return it->second;
    }
    return 0.0;
}

double Poly::operator()(double x) const {
    double result = 0.0;
    for (auto const& [exponent, coefficient] : coefficients) {
        result += coefficient * pow(x, exponent);
    }
    return result;
}

Poly operator+(const Poly& lhs, const Poly& rhs) {
    Poly result = lhs;
    for (auto const& [exponent, coefficient] : rhs.coefficients) {
        result[exponent] += coefficient;
    }
    return result;
}

Poly operator-(const Poly& lhs, const Poly& rhs) {
    Poly result = lhs;
    for (auto const& [exponent, coefficient] : rhs.coefficients) {
        result[exponent] -= coefficient;
    }
    return result;
}

Poly operator*(const Poly& lhs, const Poly& rhs) {
    Poly result;
    for (auto const& [exp1, coeff1] : lhs.coefficients) {
        for (auto const& [exp2, coeff2] : rhs.coefficients) {
            if (coeff1 != 0.0 && coeff2 != 0.0) {
                 result[exp1 + exp2] += coeff1 * coeff2;
            }
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Poly& poly) {
    if (poly.coefficients.empty()) {
        os << "0";
        return os;
    }

    bool anythingPrinted = false;
    
    for (auto it = poly.coefficients.rbegin(); it != poly.coefficients.rend(); ++it) {
        double coeff = it->second;
        int exp = it->first;

        if (std::abs(coeff) < 1e-9) continue;

        if (anythingPrinted) {
            os << (coeff > 0 ? " + " : " - ");
            coeff = std::abs(coeff);
        } else {
            if (coeff < 0) {
                os << "-";
                coeff = std::abs(coeff);
            }
        }
        
        if (std::abs(coeff - 1.0) > 1e-9 || exp == 0) {
            os << coeff;
        }

        if (exp > 0) {
            os << "x";
        }
        if (exp > 1) {
            os << "^" << exp;
        }

        anythingPrinted = true;
    }
    
    if (!anythingPrinted) {
        os << "0";
    }
    
    return os;
}