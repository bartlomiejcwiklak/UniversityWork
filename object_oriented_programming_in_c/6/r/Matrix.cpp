#include "Matrix.h"
#include <stdexcept>

Matrix::MatrixData::MatrixData(int r, int c, bool init) 
    : rows(r), cols(c), refCount(1) {
    
    if (rows < 0 || cols < 0) {
        throw MatrixIndexOutOfBounds("Matrix dimensions cannot be negative");
    }
    
    if (rows == 0 || cols == 0) {
        data = nullptr;
        rows = 0;
        cols = 0;
        return;
    }

    data = new double*[rows];
    double* block = new double[rows * cols];
    
    for (int i = 0; i < rows; ++i) {
        data[i] = block + i * cols;
    }

    if (init) {
        for (int i = 0; i < rows * cols; ++i) {
            block[i] = 0.0;
        }
    }
}

Matrix::MatrixData::~MatrixData() {
    if (data != nullptr) {
        delete[] data[0];
        delete[] data;
    }
}

Matrix::MatrixData* Matrix::MatrixData::detach() {
    if (refCount == 1) {
        return this;
    }

    MatrixData* newData = new MatrixData(rows, cols, false);
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            newData->data[i][j] = data[i][j];
        }
    }

    refCount--;
    return newData;
}

Matrix::Proxy::Proxy(Matrix& m, int row, int col) 
    : mat(m), r(row), c(col) {
}

Matrix::Proxy::operator double() const {
    return mat.pData->data[r][c];
}

Matrix::Proxy& Matrix::Proxy::operator=(double val) {
    mat.pData = mat.pData->detach();
    mat.pData->data[r][c] = val;
    return *this;
}

Matrix::Proxy& Matrix::Proxy::operator=(const Proxy& other) {
    double val = other;
    return *this = val;
}

Matrix::Proxy& Matrix::Proxy::operator+=(double val) {
    double temp = *this;
    return *this = temp + val;
}

Matrix::Proxy& Matrix::Proxy::operator-=(double val) {
    double temp = *this;
    return *this = temp - val;
}

Matrix::Proxy& Matrix::Proxy::operator*=(double val) {
    double temp = *this;
    return *this = temp * val;
}

Matrix::Proxy& Matrix::Proxy::operator/=(double val) {
    double temp = *this;
    return *this = temp / val;
}

Matrix::Matrix(int rows, int cols)
    : pData(new MatrixData(rows, cols, true)) {
}

Matrix::Matrix(const Matrix& other)
    : pData(other.pData) {
    pData->refCount++;
}

Matrix::~Matrix() {
    if (--pData->refCount == 0) {
        delete pData;
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    if (--pData->refCount == 0) {
        delete pData;
    }

    pData = other.pData;
    pData->refCount++;
    return *this;
}

int Matrix::getRows() const {
    return pData->rows;
}

int Matrix::getCols() const {
    return pData->cols;
}

double Matrix::operator()(int r, int c) const {
    if (r < 0 || r >= pData->rows || c < 0 || c >= pData->cols) {
        throw MatrixIndexOutOfBounds();
    }
    return pData->data[r][c];
}

Matrix::Proxy Matrix::operator()(int r, int c) {
    if (r < 0 || r >= pData->rows || c < 0 || c >= pData->cols) {
        throw MatrixIndexOutOfBounds();
    }
    return Proxy(*this, r, c);
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (pData->rows != other.pData->rows || pData->cols != other.pData->cols) {
        throw MatrixDimensionMismatch("Matrices must have same dimensions for addition");
    }

    Matrix result(pData->rows, pData->cols);
    for (int i = 0; i < pData->rows; ++i) {
        for (int j = 0; j < pData->cols; ++j) {
            result.pData->data[i][j] = pData->data[i][j] + other.pData->data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (pData->rows != other.pData->rows || pData->cols != other.pData->cols) {
        throw MatrixDimensionMismatch("Matrices must have same dimensions for subtraction");
    }

    Matrix result(pData->rows, pData->cols);
    for (int i = 0; i < pData->rows; ++i) {
        for (int j = 0; j < pData->cols; ++j) {
            result.pData->data[i][j] = pData->data[i][j] - other.pData->data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (pData->cols != other.pData->rows) {
        throw MatrixDimensionMismatch("Inner dimensions must match for multiplication");
    }

    Matrix result(pData->rows, other.pData->cols);
    for (int i = 0; i < result.pData->rows; ++i) {
        for (int j = 0; j < result.pData->cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < pData->cols; ++k) {
                sum += pData->data[i][k] * other.pData->data[k][j];
            }
            result.pData->data[i][j] = sum;
        }
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (pData->rows != other.pData->rows || pData->cols != other.pData->cols) {
        throw MatrixDimensionMismatch("Matrices must have same dimensions for += operator");
    }
    
    pData = pData->detach();
    
    for (int i = 0; i < pData->rows; ++i) {
        for (int j = 0; j < pData->cols; ++j) {
            pData->data[i][j] += other.pData->data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (pData->rows != other.pData->rows || pData->cols != other.pData->cols) {
        throw MatrixDimensionMismatch("Matrices must have same dimensions for -= operator");
    }

    pData = pData->detach();

    for (int i = 0; i < pData->rows; ++i) {
        for (int j = 0; j < pData->cols; ++j) {
            pData->data[i][j] -= other.pData->data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    *this = *this * other;
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    if (pData == other.pData) {
        return true;
    }

    if (pData->rows != other.pData->rows || pData->cols != other.pData->cols) {
        return false;
    }

    for (int i = 0; i < pData->rows; ++i) {
        for (int j = 0; j < pData->cols; ++j) {
            if (pData->data[i][j] != other.pData->data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.pData->rows; ++i) {
        for (int j = 0; j < m.pData->cols; ++j) {
            os << m.pData->data[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m) {
    int rows, cols;
    is >> rows >> cols;

    if (!is) {
        throw MatrixReadError("Failed to read matrix dimensions");
    }

    if (rows < 0 || cols < 0) {
        throw MatrixReadError("Invalid matrix dimensions in stream");
    }

    Matrix::MatrixData* oldPData = m.pData;
    Matrix::MatrixData* newPData = new Matrix::MatrixData(rows, cols, false);

    try {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!(is >> newPData->data[i][j])) {
                    throw MatrixReadError("Failed to read matrix element");
                }
            }
        }
    } catch (...) {
        delete newPData;
        throw;
    }

    if (--oldPData->refCount == 0) {
        delete oldPData;
    }
    
    m.pData = newPData;
    return is;
}

Matrix::Proxy& Matrix::Proxy::operator++() {
    mat.pData = mat.pData->detach();
    mat.pData->data[r][c] += 1.0;
    return *this;
}

double Matrix::Proxy::operator++(int) {
    double temp = mat.pData->data[r][c];
    mat.pData = mat.pData->detach();
    mat.pData->data[r][c] += 1.0;
    return temp;
}
