#include <algorithm>
#include "matrix.h"
#include <iostream>



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
