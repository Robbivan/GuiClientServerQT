#include <algorithm>
#include "matrix.h"
#include <iostream>

MatrixSquare::MatrixSquare():size_matrix(2), matrix(std::make_unique<number[]>(4)) {
    for (size_t i = 0; i < 4; ++i) {
        matrix[i] = 2;
    }
}
MatrixSquare::MatrixSquare(size_t _size_matrix, const std::vector<number>& init_numbers):
    size_matrix(_size_matrix),
    matrix(std::make_unique<number[]>(_size_matrix*_size_matrix))
{
    std::copy(init_numbers.begin(),init_numbers.end(),matrix.get());
}

MatrixSquare::MatrixSquare(const MatrixSquare& other) :
    size_matrix(other.size_matrix),
    matrix(std::make_unique<number[]>(size_matrix*size_matrix))
{
    std::copy(other.matrix.get(), other.matrix.get() + size_matrix * size_matrix, matrix.get());
}

std::ostream& operator<<(std::ostream& out, const MatrixSquare& matrix){
    for (size_t i = 0; i < matrix.size_matrix; ++i){
       for (size_t j = 0; j <  matrix.size_matrix; ++j){
           out << matrix.matrix[i * matrix.size_matrix + j] << '\t';
       }
       out << '\n';
    }
    return out;
}

QString& operator<<(QString& s, const MatrixSquare& matrix){
    for (size_t i = 0; i < matrix.size_matrix; ++i){
       for (size_t j = 0; j <  matrix.size_matrix; ++j){
           s << matrix.matrix[i * matrix.size_matrix + j];
           s += QStringLiteral("\t\t");
       }
       s += QStringLiteral("\n");
    }
    return s;
}

MatrixSquare& MatrixSquare::operator=(const MatrixSquare &other) {
    size_matrix = other.size_matrix;
    matrix = std::make_unique<number[]>(size_matrix*size_matrix);
    std::copy(other.matrix.get(), other.matrix.get() + size_matrix * size_matrix, matrix.get());

    return *this;
}


bool MatrixSquare::operator==(const MatrixSquare &other)const{
    if (size_matrix!=other.size_matrix){
        return false;
    }
    size_t full_size_matrix =size_matrix*size_matrix;
    for (size_t i=0;i<full_size_matrix;++i){
        if(matrix[i]!=other.matrix[i]){
            return false;
        }
    }
    return true;
}

number MatrixSquare::determinant() const{
    MatrixSquare tmp = *this;
    size_t rank = tmp.gaus();
    if (rank < size_matrix) {
        return 0;
    }

    number res = 1;
    for (size_t i = 0; i < size_matrix; ++i) {
        res *= tmp.matrix[i * size_matrix + i];
    }

    return res;
}

size_t MatrixSquare::rank() const{
    MatrixSquare tmp = *this;
    return tmp.gaus();
}

MatrixSquare MatrixSquare::transposed() const{
    MatrixSquare tmp = *this;

    for (size_t i = 0; i < tmp.size_matrix; ++i){
       for (size_t j = 0; j <  tmp.size_matrix; ++j){
           tmp.matrix[i * tmp.size_matrix + j] = matrix[j * tmp.size_matrix + i];
       }
    }

    return tmp;
}

// Gauss method
size_t MatrixSquare::gaus() {
    size_t cur_row=0;
    for (size_t i = 0; i < size_matrix; ++i) {
        size_t row = cur_row;
        while (matrix[row * size_matrix + i] == 0 && row < size_matrix) {
            ++row;
        }
        if (row == size_matrix) {
            continue;
        }

        for (size_t j = cur_row; j < size_matrix && row != cur_row; ++j) {
            std::swap(matrix[row * size_matrix + j], matrix[cur_row * size_matrix + j]);
            matrix[cur_row * size_matrix + j] *= -1;
        }
        for (size_t j = cur_row + 1; j < size_matrix; ++j) {
            number koef = matrix[j * size_matrix + i] / matrix[cur_row * size_matrix + i];
            for (size_t k = i; k < size_matrix; ++k) {
                matrix[j * size_matrix + k] -= matrix[cur_row * size_matrix + k] * koef;
            }
        }
        ++cur_row;
    }
    return cur_row;
}
