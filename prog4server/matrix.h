#ifndef MATRIX_H
#define MATRIX_H
#include <memory>
#include <vector>
#include <cstddef>
#include <QString>
#include <iostream>


using std::size_t;

template<typename number>
class Matrix{
public:
    Matrix();
    Matrix(size_t _size_row, size_t _size_col,  const std::vector<number>& init_numbers);

    Matrix(const Matrix&);
    Matrix(Matrix&&)noexcept=default;
    Matrix& operator=(const Matrix&);
    Matrix& operator=(Matrix&&)noexcept = default;
    bool operator==(const Matrix&)const;


    Matrix transposed()const;
    size_t rank()const;



    template<typename V>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<V>& matrix);

    template<typename V>
    friend QString& operator<<(QString& out, const Matrix<V>& matrix);




protected:
    size_t size_row;
    size_t size_col;
    // return rank matrix
    size_t gaus();
    std::unique_ptr<number[]> matrix;
};


template<typename number>
class MatrixSquare:public Matrix<number>
{
public:
    MatrixSquare();


    MatrixSquare(size_t _size_matrix, const std::vector<number>& init_numbers);
    MatrixSquare(const MatrixSquare&);


    MatrixSquare(MatrixSquare&&)noexcept=default;
    MatrixSquare& operator=(const MatrixSquare&);
    MatrixSquare& operator=(MatrixSquare&&)noexcept = default;
    bool operator==(const MatrixSquare&)const;


    MatrixSquare transposed()const;
    number determinant()const;

    template<typename V>
    friend std::ostream& operator<<(std::ostream& out, const MatrixSquare<V>& matrix);

    template<typename V>
    friend QString& operator<<(QString& out, const MatrixSquare<V>& matrix);



};




template<typename number>
Matrix<number>::Matrix():size_row(3), size_col(2), matrix(std::make_unique<number[]>(6)){
    for (size_t i = 0; i< 6; ++i){
        matrix[i] = 3;
    }
}

template<typename number>
Matrix<number>::Matrix(size_t _size_row, size_t _size_col,  const std::vector<number>& init_numbers):
    size_row(_size_row),
    size_col(_size_col),
    matrix(std::make_unique<number[]>(_size_row*_size_col))
{
    std::copy(init_numbers.begin(),init_numbers.end(),matrix.get());
}

template<typename number>
MatrixSquare<number>::MatrixSquare():Matrix<number>(2,2, {2,2,2,2}) {}

template<typename number>
MatrixSquare<number>::MatrixSquare(size_t _size_matrix, const std::vector<number>& init_numbers):
    Matrix<number>(_size_matrix, _size_matrix,init_numbers){}

template<typename number>
Matrix<number>::Matrix(const Matrix& other)
    :size_row(other.size_row),size_col(other.size_col),
    matrix(std::make_unique<number[]>(size_row*size_col))
{
    std::copy(other.matrix.get(), other.matrix.get() + size_row * size_col, matrix.get());
}

template<typename number>
MatrixSquare<number>::MatrixSquare(const MatrixSquare& other) :
    Matrix<number>(other)
//    size_matrix(other.size_matrix),
//    matrix(std::make_unique<number[]>(size_matrix*size_matrix))
{
//    std::copy(other.matrix.get(), other.matrix.get() + size_matrix * size_matrix, matrix.get());
}

template<typename number>
std::ostream& operator<<(std::ostream& out, const MatrixSquare<number>& matrix){
    for (size_t i = 0; i < matrix.size_row; ++i){
       for (size_t j = 0; j <  matrix.size_col; ++j){
           out << matrix.matrix[i * matrix.size_row + j] << '\t';
       }
       out << '\n';
    }
    return out;
}

template<typename number>
QString& operator<<(QString& s, const MatrixSquare<number>& matrix){
    for (size_t i = 0; i < matrix.size_row; ++i){
       for (size_t j = 0; j <  matrix.size_col; ++j){
           s << matrix.matrix[i * matrix.size_row + j];
           s += QStringLiteral("\t\t");
       }
       s += QStringLiteral("\n");
    }
    return s;
}

template<typename number>
std::ostream& operator<<(std::ostream& out, const Matrix<number>& matrix){
    for (size_t i = 0; i < matrix.size_row; ++i){
       for (size_t j = 0; j <  matrix.size_col; ++j){
           out << matrix.matrix[i * matrix.size_row + j] << '\t';
       }
       out << '\n';
    }
    return out;
}

template<typename number>
QString& operator<<(QString& s, const Matrix<number>& matrix){
    for (size_t i = 0; i < matrix.size_row; ++i){
       for (size_t j = 0; j <  matrix.size_col; ++j){
           s << matrix.matrix[i * matrix.size_row + j];
           s += QStringLiteral("\t\t");
       }
       s += QStringLiteral("\n");
    }
    return s;
}

template<typename number>
Matrix<number>& Matrix<number>::operator=(const Matrix& other){
    size_col = other.size_col;
    size_row = other.size_row;
    matrix = std::make_unique<number[]>(size_row * size_col);
    std::copy(other.matrix.get(), other.matrix.get() + size_row * size_col, matrix.get());

    return *this;
}

template<typename number>
MatrixSquare<number>& MatrixSquare<number>::operator=(const MatrixSquare<number>& other) {
    this->size_col = other.size_col;
    this->size_row = other.size_row;
    this->matrix = std::make_unique<number[]>(this->size_row * this->size_col);
    std::copy(other.matrix.get(), other.matrix.get() + this->size_row * this->size_col, this->matrix.get());

    return *this;
}

template<typename number>
bool Matrix<number>::operator==(const Matrix<number> &other)const{
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

template<typename number>
bool MatrixSquare<number>::operator==(const MatrixSquare &other)const{
    if (this->size_row!=other.size_row){
        return false;
    }
    size_t full_size_matrix =this->size_row*this->size_col;
    for (size_t i=0;i<full_size_matrix;++i){
        if(this->matrix[i]!=other.matrix[i]){
            return false;
        }
    }
    return true;
}

template<typename number>
number MatrixSquare<number>::determinant() const{
    MatrixSquare tmp = *this;
    size_t rank = tmp.gaus();
    if (rank < this->size_row) {
        return 0;
    }

    number res = 1;
    for (size_t i = 0; i < this->size_row; ++i) {
        res *= tmp.matrix[i * this->size_row + i];
    }

    return res;
}

template<typename number>
size_t Matrix<number>::rank() const{
    Matrix tmp = *this;
    return tmp.gaus();
}

template<typename number>
Matrix<number> Matrix<number>::transposed() const{
    Matrix tmp = Matrix(size_col,size_row,std::vector<number>(size_col * size_row, 0));
    for (size_t i = 0; i < tmp.size_row; ++i){
       for (size_t j = 0; j <  tmp.size_col; ++j){
           tmp.matrix[i * tmp.size_row + j] = matrix[j * tmp.size_row + i];
       }
    }
    return tmp;
}

template<typename number>
MatrixSquare<number> MatrixSquare<number>::transposed() const{
    MatrixSquare tmp = *this;

    for (size_t i = 0; i < tmp.size_row; ++i){
       for (size_t j = 0; j <  tmp.size_row; ++j){
           tmp.matrix[i * tmp.size_row + j] = this->matrix[j * tmp.size_row + i];
       }
    }

    return tmp;
}

template<typename number>
size_t Matrix<number>::gaus(){
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




#endif // MATRIX_H

