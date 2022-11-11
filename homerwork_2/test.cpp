#include <gtest/gtest.h>
#include "Matrix_n_m.hpp"

template <int N, int M>
bool compare(const Matrix<N, M> &a, const Matrix<N, M> &b)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (abs(a[i][j] - b[i][j]) > 1e-5)
                return false;
    return true;
}

template <int N>
bool compare(const Matrix<N, 1> &a, const Matrix<N, 1> &b)
{
    for (int i = 0; i < N; ++i)
        if (abs(a[i] - b[i]) > 1e-5)
            return false;
    return true;
}

template <int M>
bool compare(const Matrix<1, M> &a, const Matrix<1, M> &b)
{
    for (int i = 0; i < M; ++i)
        if (abs(a[i] - b[i]) > 1e-5)
            return false;
    return true;
}

Matrix<2, 3> mat({array<double, 3>{2, 3, 7}, array<double, 3>{4, 6, 9}});
TEST(Matrix_n_m, Test_column_operations)
{
    auto res = Matrix<2, 3>({array<double, 3>{2 - 1, 3, 7}, array<double, 3>{4 - 1, 6, 9}});
    EXPECT_EQ(compare(res, mat.sum_column(0, -1)), true);
    res = Matrix<2, 3>({array<double, 3>{2, 3, 7 - 3}, array<double, 3>{4, 6, 9 - 3}});
    EXPECT_EQ(compare(res, mat.sub_column(2, 3)), true);
}
TEST(Matrix_n_m, Test_row_operations)
{
    auto res = Matrix<2, 3>({array<double, 3>{2 + 5, 3 + 5, 7 + 5}, array<double, 3>{4, 6, 9}});
    EXPECT_EQ(compare(res, mat.sum_row(0, 5)), true);
    res = Matrix<2, 3>({array<double, 3>{2, 3, 7}, array<double, 3>{4 - 3, 6 - 3, 9 - 3}});
    EXPECT_EQ(compare(res, mat.sub_row(1, 3)), true);
}
TEST(Matrix_n_m, Test_column_vec_operations)
{
    auto x = Matrix<2, 1>(array<double, 2>{1, -5});
    auto res = Matrix<2, 3>({array<double, 3>{2 + 1, 3, 7}, array<double, 3>{4 + -5, 6, 9}});
    EXPECT_EQ(compare(res, mat.sum_column_vec(x, 0)), true);
    res = Matrix<2, 3>({array<double, 3>{2, 3 - 1, 7}, array<double, 3>{4, 6 - -5, 9}});
    EXPECT_EQ(compare(res, mat.sub_column_vec(x, 1)), true);
}
TEST(Matrix_n_m, Test_row_vec_operations)
{
    auto x = Matrix<1, 3>(array<double, 3>{3, -2, 6});
    auto res = Matrix<2, 3>({array<double, 3>{2, 3, 7}, array<double, 3>{4 + 3, 6 - 2, 9 + 6}});
    EXPECT_EQ(compare(res, mat.sum_row_vec(x, 1)), true);
    res = Matrix<2, 3>({array<double, 3>{2 - 3, 3 - -2, 7 - 6}, array<double, 3>{4, 6, 9}});
    EXPECT_EQ(compare(res, mat.sub_row_vec(x, 0)), true);
}

TEST(Matrix_n_m, Test_get)
{
    EXPECT_EQ(compare(Matrix<2, 1>({2, 6}), mat.get_diag()), true);
    EXPECT_EQ(compare(Matrix<2, 1>({7, 9}), mat.get_column(2)), true);
    EXPECT_EQ(compare(Matrix<3, 1>({2, 3, 7}), mat.get_row(0)), true);
}

TEST(Matrix_n_m, Test_det_inv)
{
    auto x = Matrix<3, 3>({array<double, 3>{2, 5, 7}, array<double, 3>{6, 3, 4}, array<double, 3>{5, -2, -3}});
    auto inv_x = Matrix<3, 3>({array<double, 3>{1, -1, 1}, array<double, 3>{-38, 41, -34},
                               array<double, 3>{27, -29, 24}});
    EXPECT_EQ(compare(x.inv(), inv_x), true);
    EXPECT_EQ(abs(x.det() - -1) < 1e-5, true);
}

TEST(Matrix, Test_T)
{
    auto res = Matrix<3, 2>({array<double, 2>{2, 4}, array<double, 2>{3, 6}, array<double, 2>{7, 9}});
    EXPECT_EQ(compare(res, mat.T()), true);
    auto a = Matrix<2, 1>({1, 3});
    auto b = Matrix<1, 2>({1, 3});
    EXPECT_EQ(compare(b, a.T()), true);
    EXPECT_EQ(compare(a, b.T()), true);
}

TEST(Matrix, Mult_scal)
{
    auto res = Matrix<2, 3>({array<double, 3>{2 * 3, 3 * 3, 7 * 3}, array<double, 3>{4 * 3, 6 * 3, 9 * 3}});
    EXPECT_EQ(compare(res, mat * 3), true);
    EXPECT_EQ(compare(res, 3 * mat), true);
    auto a = Matrix<2, 1>({1, 3});
    EXPECT_EQ(compare(Matrix<2, 1>({1 * 5, 3 * 5}), a * 5), true);
    EXPECT_EQ(compare(Matrix<2, 1>({1 * 5, 3 * 5}), 5 * a), true);
    auto b = Matrix<1, 2>({1, 3});
    EXPECT_EQ(compare(Matrix<1, 2>({1 * 16, 3 * 16}), b * 16), true);
    EXPECT_EQ(compare(Matrix<1, 2>({1 * 16, 3 * 16}), 16 * b), true);
}

TEST(Matrix, Mat_opearations)
{
    auto res = Matrix<2, 3>({array<double, 3>{2 * 3, 3 * 3, 7 * 3}, array<double, 3>{4 * 3, 6 * 3, 9 * 3}});
    EXPECT_EQ(compare(mat - 2 * mat, (-1) * mat), true);
    EXPECT_EQ(compare(mat + 2 * mat, 3 * mat), true);
    auto a = Matrix<2, 1>({1, 3});
    EXPECT_EQ(compare(a - 2 * a, (-1) * a), true);
    EXPECT_EQ(compare(a + 2 * a, 3 * a), true);
    auto b = Matrix<1, 2>({1, 3});
    EXPECT_EQ(compare(b - 2 * b, (-1) * b), true);
    EXPECT_EQ(compare(b + 2 * b, 3 * b), true);
}

TEST(Matrix, Mat_Mult)
{
    auto x = Matrix<3, 3>({array<double, 3>{2, 5, 7}, array<double, 3>{6, 3, 4}, array<double, 3>{5, -2, -3}});
    auto E = Matrix<3, 3>({array<double, 3>{1, 0, 0}, array<double, 3>{0, 1, 0}, array<double, 3>{0, 0, 1}});
    EXPECT_EQ(compare(x & x.inv(), E), true);
    EXPECT_EQ(compare(x.inv() & x, E), true);

    auto a = Matrix<2, 1>({1, 3});
    auto b = Matrix<1, 2>({1, 3});
    auto res = Matrix<2, 2>({array<double, 2>{1, 3}, array<double, 2>{3, 9}});
    EXPECT_EQ(compare(a & b, res), true);
    EXPECT_EQ(abs((b & a) - 1 - 3 * 3) < 1e-5, true);

    EXPECT_EQ(compare(b & res, Matrix<1, 2>({10, 30})), true);
    EXPECT_EQ(compare(res & a, Matrix<2, 1>({10, 30})), true);
}
