#pragma once
#include <iostream>
#include "MatrixExceptions.h"

class Matrix {
private:
    struct MatrixData {
        double** data;
        int rows;
        int cols;
        int refCount;

        MatrixData(int r, int c, bool init);
        ~MatrixData();
        MatrixData* detach();
    
    private:
        MatrixData(const MatrixData&);
        MatrixData& operator=(const MatrixData&);
    };

    MatrixData* pData;

public:
    class Proxy {
        Matrix& mat;
        int r, c;
    public:
        Proxy(Matrix& m, int row, int col);

        operator double() const;
        Proxy& operator=(double val);
        Proxy& operator=(const Proxy& other);

        Proxy& operator+=(double val);
        Proxy& operator-=(double val);
        Proxy& operator*=(double val);
        Proxy& operator/=(double val);
        Proxy& operator++();
        double operator++(int);
    };

    Matrix(int rows = 1, int cols = 1);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    int getRows() const;
    int getCols() const;

    double operator()(int r, int c) const;
    Proxy operator()(int r, int c);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    friend std::istream& operator>>(std::istream& is, Matrix& m);
};