#include <algorithm>
#include "matrix.h"
#include <iostream>

Matrix::Matrix():size_row(3), size_col(2), matrix(std::make_unique<number[]>(6)){
    for (size_t i = 0; i< 6; ++i){
        matrix[i] = 3;
    }
}

Matrix::Matrix(size_t _size_row, size_t _size_col,  const std::vector<number>& init_numbers):
    size_row(_size_row),
    size_col(_size_col),
    matrix(std::make_unique<number[]>(_size_row*_size_col))
{
    std::copy(init_numbers.begin(),init_numbers.end(),matrix.get());
}


MatrixSquare::MatrixSquare():Matrix(2,2, {2,2,2,2}) {}


MatrixSquare::MatrixSquare(size_t _size_matrix, const std::vector<number>& init_numbers):
    Matrix(_size_matrix, _size_matrix,init_numbers){}


Matrix::Matrix(const Matrix& other)
    :size_row(other.size_row),size_col(other.size_col),
    matrix(std::make_unique<number[]>(size_row*size_col))
{
    std::copy(other.matrix.get(), other.matrix.get() + size_row * size_col, matrix.get());
}

MatrixSquare::MatrixSquare(const MatrixSquare& other) :
    Matrix(other)
//    size_matrix(other.size_matrix),
//    matrix(std::make_unique<number[]>(size_matrix*size_matrix))
{
//    std::copy(other.matrix.get(), other.matrix.get() + size_matrix * size_matrix, matrix.get());
}

std::ostream& operator<<(std::ostream& out, const MatrixSquare& matrix){
    for (size_t i = 0; i < matrix.size_row; ++i){
       for (size_t j = 0; j <  matrix.size_col; ++j){
           out << matrix.matrix[i * matrix.size_row + j] << '\t';
       }
       out << '\n';
    }
    return out;
}

QString& operator<<(QString& s, const MatrixSquare& matrix){
    for (size_t i = 0; i < matrix.size_row; ++i){
       for (size_t j = 0; j <  matrix.size_col; ++j){
           s << matrix.matrix[i * matrix.size_row + j];
           s += QStringLiteral("\t\t");
       }
       s += QStringLiteral("\n");
    }
    return s;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix){
    for (size_t i = 0; i < matrix.size_row; ++i){
       for (size_t j = 0; j <  matrix.size_col; ++j){
           out << matrix.matrix[i * matrix.size_row + j] << '\t';
       }
       out << '\n';
    }
    return out;
}

QString& operator<<(QString& s, const Matrix& matrix){
    for (size_t i = 0; i < matrix.size_row; ++i){
       for (size_t j = 0; j <  matrix.size_col; ++j){
           s << matrix.matrix[i * matrix.size_row + j];
           s += QStringLiteral("\t\t");
       }
       s += QStringLiteral("\n");
    }
    return s;
}

Matrix& Matrix::operator=(const Matrix& other){
    size_col = other.size_col;
    size_row = other.size_row;
    matrix = std::make_unique<number[]>(size_row * size_col);
    std::copy(other.matrix.get(), other.matrix.get() + size_row * size_col, matrix.get());

    return *this;
}

MatrixSquare& MatrixSquare::operator=(const MatrixSquare& other) {
    size_col = other.size_col;
    size_row = other.size_row;
    matrix = std::make_unique<number[]>(size_row * size_col);
    std::copy(other.matrix.get(), other.matrix.get() + size_row * size_col, matrix.get());

    return *this;
}


bool Matrix::operator==(const Matrix &other)const{
    if (size_row!=other.size_row||size_col!=other.size_col){
        return false;
    }
    size_t full_size_matrix =size_row*size_col;
    for (size_t i=0;i<full_size_matrix;++i){
        if(matrix[i]!=other.matrix[i]){
            return false;
        }
    }
    return true;

}

bool MatrixSquare::operator==(const MatrixSquare &other)const{
    if (size_row!=other.size_row){
        return false;
    }
    size_t full_size_matrix =size_row*size_col;
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
    if (rank < size_row) {
        return 0;
    }

    number res = 1;
    for (size_t i = 0; i < size_row; ++i) {
        res *= tmp.matrix[i * size_row + i];
    }

    return res;
}

size_t Matrix::rank() const{
    Matrix tmp = *this;
    return tmp.gaus();
}

Matrix Matrix::transposed() const{
    Matrix tmp = Matrix(size_col,size_row,std::vector<number>(size_col * size_row, 0));
    for (size_t i = 0; i < tmp.size_row; ++i){
       for (size_t j = 0; j <  tmp.size_col; ++j){
           tmp.matrix[i * tmp.size_row + j] = matrix[j * tmp.size_row + i];
       }
    }
    return tmp;
}

MatrixSquare MatrixSquare::transposed() const{
    MatrixSquare tmp = *this;

    for (size_t i = 0; i < tmp.size_row; ++i){
       for (size_t j = 0; j <  tmp.size_row; ++j){
           tmp.matrix[i * tmp.size_row + j] = matrix[j * tmp.size_row + i];
       }
    }

    return tmp;
}


size_t Matrix::gaus(){
    size_t cur_row=0;
    for (size_t i = 0; i < size_row; ++i) {
        size_t row = cur_row;
        while (matrix[row * size_row + i] == 0 && row < size_row) {
            ++row;
        }
        if (row == size_row) {
            continue;
        }

        for (size_t j = cur_row; j < size_col && row != cur_row; ++j) {
            std::swap(matrix[row * size_row + j], matrix[cur_row * size_row + j]);
            matrix[cur_row * size_row + j] *= -1;
        }
        for (size_t j = cur_row + 1; j < size_row; ++j) {
            number koef = matrix[j * size_row + i] / matrix[cur_row * size_row + i];
            for (size_t k = i; k < size_col; ++k) {
                matrix[j * size_row + k] -= matrix[cur_row * size_row + k] * koef;
            }
        }
        ++cur_row;
    }
    return cur_row;
}


//// Gauss method
//size_t MatrixSquare::gaus() {
//    size_t cur_row=0;
//    for (size_t i = 0; i < size_matrix; ++i) {
//        size_t row = cur_row;
//        while (matrix[row * size_matrix + i] == 0 && row < size_matrix) {
//            ++row;
//        }
//        if (row == size_matrix) {
//            continue;
//        }

//        for (size_t j = cur_row; j < size_matrix && row != cur_row; ++j) {
//            std::swap(matrix[row * size_matrix + j], matrix[cur_row * size_matrix + j]);
//            matrix[cur_row * size_matrix + j] *= -1;
//        }
//        for (size_t j = cur_row + 1; j < size_matrix; ++j) {
//            number koef = matrix[j * size_matrix + i] / matrix[cur_row * size_matrix + i];
//            for (size_t k = i; k < size_matrix; ++k) {
//                matrix[j * size_matrix + k] -= matrix[cur_row * size_matrix + k] * koef;
//            }
//        }
//        ++cur_row;
//    }
//    return cur_row;
//}
