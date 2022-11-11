#ifndef MATRIX_N_M
#define MATRIX_N_M
#include <bits/stdc++.h>

using namespace std;

template <int N, int M> class Matrix {
private:
  Matrix<N, M> column_op(double x, int pos, int op);
  Matrix<N, M> row_op(double x, int pos, int op);
  Matrix<N, M> column_op_vec(const Matrix<N, 1> &b, int pos, int op);
  Matrix<N, M> row_op_vec(const Matrix<1, M> &b, int pos, int op);

protected:
  array<array<double, M>, N> mat;

public:
  explicit Matrix(const array<array<double, M>, N> &x) : mat(x) {}
  Matrix() = default;
  typedef array<array<double, M>, N> *iterator;
  iterator begin() { return mat.begin(); }
  iterator end() { return mat.end(); }

  Matrix<N, M> &operator=(const Matrix<N, M> &x) {
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        mat[i][j] = x[i][j];
    return *this;
  }
  Matrix(const Matrix<N, M> &x) {
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        mat[i][j] = x[i][j];
  }

  Matrix<M, N> T() const;
  Matrix<N, M> inv();
  array<double, M> &operator[](int pos) { return mat[pos]; }
  array<double, M> operator[](int pos) const { return mat[pos]; }
  Matrix<N, M> sum_column(int pos, int x) { return column_op(x, pos, 0); }
  Matrix<N, M> sub_column(int pos, int x) { return column_op(x, pos, 1); }
  Matrix<N, M> sum_row(int pos, int x) { return row_op(x, pos, 0); }
  Matrix<N, M> sub_row(int pos, int x) { return row_op(x, pos, 1); }
  Matrix<N, M> sum_column_vec(const Matrix<N, 1> &b, int pos) {
    return column_op_vec(b, pos, 0);
  }
  Matrix<N, M> sub_column_vec(const Matrix<N, 1> &b, int pos) {
    return column_op_vec(b, pos, 1);
  }
  Matrix<N, M> sum_row_vec(const Matrix<1, M> &b, int pos) {
    return row_op_vec(b, pos, 0);
  }
  Matrix<N, M> sub_row_vec(const Matrix<1, M> &b, int pos) {
    return row_op_vec(b, pos, 1);
  }
  bool compare(const Matrix<N, M> &a, const Matrix<N, M> &b);
  Matrix<min(N, M), 1> get_diag();
  Matrix<N, 1> get_column(int num);
  Matrix<M, 1> get_row(int num);
  double det();
  void printer() const;
};

template <int N> class Matrix<1, N> {
  friend class Matrix<N, 1>;

protected:
  array<double, N> vec;

public:
  Matrix() = default;
  typedef array<double, N> *iterator;
  iterator begin() { return vec.begin(); }
  iterator end() { return vec.end(); }
  double &operator[](int pos) { return vec[pos]; }
  double operator[](int pos) const { return vec[pos]; }
  explicit Matrix(const array<double, N> &x) {
    for (int i = 0; i < N; ++i)
      vec[i] = x[i];
  }
  Matrix<1, N> &operator=(const Matrix<1, N> &x) {
    for (int i = 0; i < N; ++i)
      vec[i] = x[i];
    return *this;
  }

  Matrix(const Matrix<1, N> &x) {
    for (int i = 0; i < N; ++i)
      vec[i] = x[i];
  }

  Matrix<N, 1> T() const { return Matrix<N, 1>(vec); }
  void printer() const {
    for (const double &i : vec)
      cout << i << ", ";
    cout << '\n';
  }
};

template <int N> class Matrix<N, 1> {
  Matrix<1, N> mat;

public:
  Matrix<N, 1> &operator=(const Matrix<N, 1> &x) {
    for (int i = 0; i < N; ++i)
      mat[i] = x[i];
    return *this;
  }
  Matrix(const Matrix<N, 1> &x) {
    for (int i = 0; i < N; ++i)
      mat[i] = x[i];
  }
  Matrix() = default;
  explicit Matrix(const array<double, N> &x) : mat(x) {}
  Matrix<1, N> T() const { return mat; }
  void printer() const {
    for (const double &i : mat.vec)
      cout << i << "\n";
  }
  typedef array<double, N> *iterator;
  iterator begin() { return mat.begin(); }
  iterator end() { return mat.end(); }
  double &operator[](int pos) { return mat[pos]; }
  double operator[](int pos) const { return mat[pos]; }
};
#include "Matrix_n_m.tpp"
#endif