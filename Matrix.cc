

#include "Matrix.hh"

/*
 * Clase Matrix
 */
  using namespace std;

  Matrix::Matrix(){
    M = vector<<vector<long double> >(0);
    row = col = 0;
  }
  Matrix::Matrix(int n, int m){

    M = vector<<vector<long double> >(n,vector<long double>(m,0));
    row = n;
    col = m;
  }

  Matrix Matrix::operator+(Matrix a) const{
      if(this->row != a.row or this->col != a.col)
          return Matrix();
      Matrix aux = this;
      for(int i = 0; i < this->row; ++i)
        for(int j = 0; j < this->col; ++j)
          aux.M[i][j] += a.M[i][j];

      return aux;


  }

//  Matrix  Matrix::operator*(const Matrix& a) const;
  Matrix  Matrix::operator-(const Matrix& a) const{
    if(this->row != a.row or this->col != a.col)
          return Matrix();
      Matrix aux = this;
      for(int i = 0; i < this->row; ++i)
        for(int j = 0; j < this->col; ++j)
          aux.M[i][j] -= a.M[i][j];

      return aux;
  }
//  Matrix Matrix::inverse() const;

  void  Matrix::operator=(const Matrix& a){
      this->row = a.row;
      this->col = a.col;
      this->M = a.M;
  }
  bool  Matrix::operator==(const Matrix& a) const{
      return this->col == a.col and this->row == a.row and a.M == this->M;

  }
  bool  Matrix::operator!=(const Matrix& a) const{
      return (not a==this);
  }

  Matrix Matrix::identity(int n){
      Matrix a(n,n);
      for(int i = 0; i < n; ++i)
        a.M[i][i] = 1;
  }


