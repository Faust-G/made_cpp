
#include "Matrix_n_m.h"
template<int N, int M>
Matrix<N, M> Matrix<N, M>::column_op(double x, int pos, int op){
    Matrix<N, M> res = *this;
    for(int i = 0;i< N;++i) {
        if (op == 0)
            res[i][pos] = mat[i][pos] + x;
        if(op == 1)
            res[i][pos] = mat[i][pos] - x;
    }
    return res;
}
template<int N, int M>
Matrix<N, M> Matrix<N, M>::row_op(double x, int pos, int op){
    Matrix<N, M> res = *this;
    for(int i = 0;i< M;++i) {
        if (op == 0)
            res[pos][i] = mat[pos][i] + x;
        if(op == 1)
            res[pos][i] = mat[pos][i] - x;
    }
    return res;
}
template<int N, int M>
Matrix<N, M> Matrix<N, M>::column_op_vec(const Matrix<N, 1>& b, int pos, int op){
    Matrix<N, M> res = *this;
    for(int i = 0;i< N;++i) {
        if (op == 0)
            res[i][pos] = mat[i][pos] + b[i];
        if(op == 1)
            res[i][pos] = mat[i][pos] - b[i];
    }
    return res;
}
template<int N, int M>
Matrix<N, M> Matrix<N, M>::row_op_vec(const Matrix<1, M>& b, int pos, int op){
    Matrix<N, M> res = *this;
    for(int i = 0;i< M;++i) {
        if (op == 0)
            res[pos][i] = mat[pos][i] + b[i];
        if(op == 1)
            res[pos][i] = mat[pos][i] - b[i];
    }
    return res;
}
template<int N,int M>
Matrix<M, N> Matrix<N, M>::T(){
    Matrix<M, N> res;
    for(int i = 0;i<N;++i)
        for(int j = 0;j<M;++j)
            res[j][i]=mat[i][j];
    return res;
}
template<int N,int M>
Matrix<N, M> Matrix<N, M>::inv(){
    assert(det() != 0);
    auto x = mat, ob = mat;
    for(int i = 0;i<N;++i)
        for(int j = 0;j<N;++j){
            if(i == j)
                ob[i][j] = 1;
            else
                ob[i][j]=0;
        }
    for (int k = 0; k < N - 1; k++) {
        for (int i = k + 1; i < N; i++) {
            double  tmp = -x[i][k] / x[k][k];
            for (int j = 0; j < N; j++) {
                x[i][j] += x[k][j] * tmp;
                ob[i][j] +=ob[k][j] * tmp;
            }
        }
    }
    for (int k = N - 1; k >= 0; k--) {
        for(int i = 0;i<N;++i)
            ob[k][i] /= x[k][k];
        x[k][k] = 1;
        for (int i = k - 1; i >= 0; i--) {
            double  tmp = -x[i][k];
            for (int j = 0; j < N; j++) {
                x[i][j] += x[k][j] * tmp;
                ob[i][j] +=ob[k][j] * tmp;
            }
        }
    }
    return Matrix<N, M>(ob);
}
template<int N,int M>
Matrix<min(N, M),1> Matrix<N, M>::get_diag(){
    Matrix<min(N, M),1> res;
    int pos = 0;
    while(pos < min(N, M)){
        res[pos] = mat[pos][pos];
        ++pos;
    }
    return res;
}
template<int N,int M>
Matrix<N,1>  Matrix<N, M>::get_column(int num){
    Matrix<N,1> res;
    for(int i = 0;i< N;++i)
        res[i] = mat[i][num];
    return res;
}
template<int N,int M>
Matrix<M,1> Matrix<N, M>::get_row(int num){
    Matrix<M,1> res;
    for(int i = 0;i< M;++i)
        res[i] = mat[num][i];
    return res;
}
template<int N,int M>
double Matrix<N, M>::det(){
    assert(N==M);
    auto x = mat;
    for (int k = 0; k < N - 1; k++) {
        for (int i = k + 1; i < N; i++) {
            double  tmp = -x[i][k] / x[k][k];
            for (int j = 0; j < N; j++)
                x[i][j] += x[k][j] * tmp;
        }
    }
    double res = 1;
    for(int i =0;i<N;++i)
        res*=x[i][i];
    return res;
}
template<int N,int M>
void Matrix<N, M>::printer(){
    for(const auto& i : mat) {
        for (const auto& j : i)
            cout<<j<<", ";
        cout<<'\n';
    }
}
template<int N, int M>
Matrix<N, M> operator * (double a, const Matrix<N, M>& b){
    return b * a;
}