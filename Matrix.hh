// Definition of class Matrix
//supports matrix, vector
//multiplication,inverse,sum,minimum and maximum search with position


#ifndef _MATRIX_
#define _MATRIX_

#include <vector>
#include <iostream>
#include <algorithm>
#include <Rational>

/*
 * Clase Matrix
 */
class Matrix {


private:

  vector<vector<Rational>> M;

public:

  Matrix();
  Matrix(int n, int m);

  Matrix override operator+(const Matrix& a) const;

  Matrix override operator*(const Matrix& a) const;
  Matrix override operator-(const Matrix& a) const;
  Matrix inverse() const;
  Matrix override operator==(const Matrix& a) const;
  Matrix override operator!=(const Matrix& a) const;

};

#endif

