#ifndef MATRIX_H
#define MATRIX_H
#include <memory>
#include <vector>
#include <cstddef>
#include "number.h"

using std::size_t;


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



    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
    friend QString& operator<<(QString& out, const Matrix& matrix);

protected:
    size_t size_row;
    size_t size_col;
    // return rank matrix
    size_t gaus();
    std::unique_ptr<number[]> matrix;
};



class MatrixSquare:public Matrix
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


    friend std::ostream& operator<<(std::ostream& out, const MatrixSquare& matrix);
    friend QString& operator<<(QString& out, const MatrixSquare& matrix);

};


#endif // MATRIX_H

