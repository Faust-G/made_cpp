#include "Matrix_n_m.hpp"
using namespace std;
 
int main()
{
   // array<array<double, 3>, 2> v{array<double, 3>{2, 3, 7}, array<double, 3>{4, 6, 9}};
   // Matrix<2, 3> m(v);
   // Matrix<1, 3> k(v[0]);
   // m.printer();
   // (m.sub_row(1, 2)).printer();
   // (m.T()).printer();
   // auto a = k.T();
   // auto b = m.T();
   // k.printer();
   // (3 * a).printer();
   Matrix<2, 3> mat({array<double, 3>{2, 3, 7}, array<double, 3>{4, 6, 9}});
   auto res = mat;
   res.printer();
   // mat.sum_column(0, -1).printer();
   cout<<compare(res, mat.sum_column(0, -1));
}