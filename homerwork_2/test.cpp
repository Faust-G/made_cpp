#include <gtest/gtest.h>
#include "Matrix_n_m.hpp"
 
 
// Matrix<N, M> sum_column(int pos, int x){
//         return column_op(x, pos, 0);
//     }
//     Matrix<N, M> sub_column(int pos, int x){
//         return column_op(x, pos, 0);
//     }
//     Matrix<N, M> sum_row(int pos, int x){
//         return row_op(x, pos, 0);
//     }
//     Matrix<N, M> sub_row(int pos, int x){
//         return row_op(x, pos, 0);
//     }
//     Matrix<N, M> sum_column_vec(const Matrix<N, 1>& b, int pos){
//         return column_op(b, pos, 0);
//     }
//     Matrix<N, M> sub_column_vec(const Matrix<N, 1>& b, int pos){
//         return column_op(b, pos, 1);
//     }
//     Matrix<N, M> sum_row_vec(const Matrix<1, M>& b, int pos){
//         return row_op(b, pos, 0);
//     }
//     Matrix<N, M> sub_row_vec(const Matrix<1, M>& b, int pos){
//         return row_op(b, pos, 1);
//     }
Matrix<2, 3> mat({array<double, 3>{2, 3, 7}, array<double, 3>{4, 6, 9}});
TEST(Matrix_n_m, Test_column_operations)
{
    auto res = Matrix<2, 3>({array<double, 3>{1, 3, 7}, array<double, 3>{3, 6, 9}});
    EXPECT_EQ(compare(res, mat.sum_column(0, -1)), true);
    res = Matrix<2, 3>({array<double, 3>{2, 3, 10}, array<double, 3>{4, 6, 12}});
    EXPECT_EQ(compare(res, mat.sub_column(2, 3)), true);
 
}
TEST(Matrix_n_m, Test_row_operations)
{
    auto res = Matrix<2, 3>({array<double, 3>{1, 3, 7}, array<double, 3>{3, 6, 9}});
    EXPECT_EQ(compare(res, mat.sum_row(0, 5)), true);
    res = Matrix<2, 3>({array<double, 3>{2, 3, 10}, array<double, 3>{4, 6, 12}});
    EXPECT_EQ(compare(res, mat.sub_column(2, 3)), true);
 
}