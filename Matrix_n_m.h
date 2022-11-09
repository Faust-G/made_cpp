#ifndef MATRIX_N_M
#define MATRIX_N_M
#include <bits/stdc++.h>
 
using namespace std;
 
template<int N, int M>
class Matrix {
private:
    Matrix<N, M> column_op(double x, int pos, int op);
    Matrix<N, M> row_op(double x, int pos, int op);
    Matrix<N, M> column_op_vec(const Matrix<N, 1>& b, int pos, int op);
    Matrix<N, M> row_op_vec(const Matrix<1, M>& b, int pos, int op);
protected:
    array<array<double,M>, N> mat;
public:
    explicit Matrix(const array<array<double,M>, N>& x) : mat(x){}
    Matrix()=default;
    typedef array<array<double,M>, N>* iterator;
    iterator begin();
    iterator end();
    Matrix<M, N> T();
    array<double,M>& operator [] (int pos);
    array<double,M> operator [](int pos)const;
    Matrix<N, M> sum_column(int pos, int x);
    Matrix<N, M> sub_column(int pos, int x);
    Matrix<N, M> sum_row(int pos, int x);
    Matrix<N, M> sub_row(int pos, int x);
    Matrix<N, M> sum_column_vec(const Matrix<N, 1>& b, int pos);
    Matrix<N, M> sub_column_vec(const Matrix<N, 1>& b, int pos);
    Matrix<N, M> sum_row_vec(const Matrix<1, M>& b, int pos);
    Matrix<N, M> sub_row_vec(const Matrix<1, M>& b, int pos);
    Matrix<min(N, M),1> get_diag();
    Matrix<N,1>  get_column(int num);
    Matrix<M,1> get_row(int num);
    double det();
    void printer();
};
#include"Matrix_n_m.tpp"
#endif