#ifndef MATRIX_H
#define MATRIX_H
#include <memory>
#include <vector>
#include <cstddef>
#include "number.h"

using std::size_t;

class MatrixSquare
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
    size_t rank()const;

    friend std::ostream& operator<<(std::ostream& out, const MatrixSquare& matrix);
    friend QString& operator<<(QString& out, const MatrixSquare& matrix);

private:
    size_t size_matrix;
    // smart pointers since C++11
    std::unique_ptr<number[]> matrix;

    // return rank matrix
    size_t gaus();
};


#endif // MATRIX_H

