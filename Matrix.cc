

#include "Matrix.hh"

/*
 * Clase Matrix
 */

  Matrix::Matrix(){
    M = vector<<vector<long long> >();
    row = col = 0;
  }
  Matrix::Matrix(int n, int m){

    M = vector<<vector<long long> >(n,vector<long long>(m,0));
    row = n;
    col = m;
  }

  Matrix  Matrix::operator+(const Matrix& a) const{
      if(this.row != a.row or this.col != a.col)
          return Matrix();
      Matrix aux = this;
      for(int i = 0; i < this.row; ++i)
        for(int j = 0; j < this.col; ++j)
          aux.M[i][j] += a.M[i][j];

      return aux;


  }

  Matrix  Matrix::operator*(const Matrix& a) const;
  Matrix  Matrix::operator-(const Matrix& a) const;
  Matrix Matrix::inverse() const;

  void  Matrix::operator=(const Matrix& a) const{

  }
  Matrix  Matrix::operator==(const Matrix& a) const;
  Matrix  Matrix::operator!=(const Matrix& a) const;

  Matrix  Matrix::operator>(const Matrix& a) const;

  Matrix  Matrix::operator<(const Matrix& a) const;


