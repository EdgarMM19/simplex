
#ifndef _MATRIX_
#define _MATRIX_

#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;
/*
 * Clase Matrix
 */
class Matrix {


private:

  vector<vector<long double> > M;
  int row,col;
public:

  Matrix();
  Matrix(int n, int m);

  Matrix operator+(const Matrix& a) const;

  Matrix operator*(const Matrix& a) const;
  Matrix operator-(const Matrix& a) const;

  Matrix operator=(const Matrix& a);
  Matrix inverse() const;
  bool operator==(const Matrix& a) const;
  bool operator!=(const Matrix& a) const;

  static Matrix identity(int n);

};

#endif

