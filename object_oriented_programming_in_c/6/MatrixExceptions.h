#pragma once
#include <string>

class MatrixException {
protected:
    std::string message;

public:
    MatrixException(const std::string& msg = "") : message(msg) {}
    virtual ~MatrixException() {}
    
    const char* what() const {
        return message.c_str();
    }
};

class MatrixIndexOutOfBounds : public MatrixException {
public:
    MatrixIndexOutOfBounds(const std::string& msg = "Matrix index is out of bounds")
        : MatrixException(msg) {}
};

class MatrixReadError : public MatrixException {
public:
    MatrixReadError(const std::string& msg = "Error reading matrix from stream")
        : MatrixException(msg) {}
};