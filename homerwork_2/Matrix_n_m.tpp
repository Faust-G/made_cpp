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
template<int N, int M>
Matrix<N, M>  make_operation(const Matrix<N, M> &  a, const Matrix<N, M> &  b, int op){
    Matrix<N, M>  res;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            if (op == 0)
                res[i][j] = a[i][j] + b[i][j];
            if (op == 1)
                res[i][j] = a[i][j] - b[i][j];
            if (op == 2)
                res[i][j] = a[i][j] * b[i][j];
        }
    return res;
}
template<int N, int M>
Matrix<N, M>  operator * (const Matrix<N, M> &  a, const Matrix<N, M> &  b){
    return make_operation(a,b, 2);
}
template<int N, int M>
Matrix<N, M>  operator - (const Matrix<N, M> &  a, const Matrix<N, M> &  b){
    return make_operation(a,b, 1);
}
template<int N, int M>
Matrix<N, M>  operator + (const Matrix<N, M> &  a, const Matrix<N, M> &  b){
    return make_operation(a,b, 0);
}
 
 
template<int N, int M>
Matrix<N, M> operator * (const Matrix<N, M> &  a, double x){
    Matrix<N, M>  res;
    for(int i =0;i<N;++i)
        for(int j =0;j<M;++j)
            res[i][j]=a[i][j]*x;
    return res;
}
 
template<int N>
Matrix<N, 1>  make_operation(const Matrix<N, 1> &  a, const Matrix<N, 1> &  b, int op){
    Matrix<N, 1>  res;
    for(int i = 0;i<N;++i) {
        if(op == 0)
            res[i] = a[i] + b[i];
        if(op == 1)
            res[i] = a[i] - b[i];
        if(op == 2)
            res[i] = a[i] * b[i];
    }
    return res;
}
template<int N>
Matrix<1, N>  make_operation(const Matrix<1, N> &  a, const Matrix<1, N> &  b, int op){
    return make_operation(a.T(), b.T(), op).T();
}
 
template<int N>
Matrix<N, 1> operator * (const Matrix<N, 1> &  a, double x){
    Matrix<N, 1>  res;
    for (int i = 0; i < N; ++i)
        res[i] = a[i] * x;
    return res;
}
template<int N>
Matrix<1, N> operator * (const Matrix<1, N> &  a, int x){
    Matrix<1, N>  res;
    for (int i = 0; i < N; ++i)
        res[i] = a[i] * x;
    return res;
}
template<int N, int M, int K>
Matrix<N, K>  operator & (const Matrix<N, M> &  a, const Matrix<M, K> &  b){
    Matrix<N, K>  res;
    for(int i =0;i<N;++i)
        for(int j = 0;j<K;++j) {
            int l2 =0;
            for (int l = 0; l < M; ++l)
                l2 += a[i][l] * b[l][j];
            res[i][j] = l2;
        }
    return res;
}
template<int N, int M>
Matrix<N, 1>  operator & (const Matrix<N, M> &  a, const Matrix<M, 1> &  b){
    Matrix<N, 1>  res;
    for(int i =0;i<N;++i) {
        int l2 = 0;
        for (int j = 0; j < M; ++j)
            l2 += a[i][j] * b[j];
        res[i] = l2;
    }
    return res;
}
template<int N, int M>
Matrix<1, M>   operator & (const Matrix<1, N> &  a, const Matrix<N, M> &  b){
    Matrix<1, M>  res;
    for(int i =0;i<M;++i) {
        int l2 = 0;
        for (int j = 0; j < N; ++j)
            l2 += a[j] * b[j][i];
        res[i] = l2;
    }
    return res;
}
template<int N, int M>
Matrix<N, M>  operator & (const Matrix<N, 1> &  a, const Matrix<1, M> &  b){
    Matrix<N, M>  res;
    for(int i = 0;i<N;++i)
        for(int j =0;j<M;++j)
            res[i][j] =a[i]*b[j];
    return res;
}
template<int N>
double operator & (const Matrix<1, N> &  a, const Matrix<N, 1> &  b){
    double res = 0;
    for(int i = 0;i<N;++i)
        res+=a[i]*b[i];
    return res;
}
 
template<int N, int M>
bool compare(const Matrix<N, M>& a, const Matrix<N, M>& b){
        for(int i =0;i<N;++i)
        for(int j =0;j<M;++j)
            if(a[i][j]!=b[i][j])
            return false;
    return true;
}
 
template<int N>
bool compare(const Matrix<N, 1>& a, const Matrix<N, 1>& b){
    for(int i =0;i<N;++i)
        if(a[i]!=b[i])
            return false;
    return true;
}
 
template<int M>
bool compare(const Matrix<1, M>& a, const Matrix<1, M>& b){
        for(int i =0;i<M;++i)
            if(a[i]!=b[i])
                return false;
    return true;
}