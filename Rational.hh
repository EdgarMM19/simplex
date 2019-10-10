
#ifndef _RATIONAL_
#define _RATIONAL_
#include <iostream>


/*
 * Clase Matrix
 */

class Rational {


private:

  int den,num;
  int _gcd();
  void simplify();

public:

  
  Rational();
  Rational(int a,int b);  
  Rational override operator+(const Rational& a) const;

  Rational override operator*(const Rational& a) const;
  Rational override operator-(const Rational& a) const;
  Rational override operator/(const Rational& a) const;

  Rational override operator==(const Rational& a) const;
  Rational override operator!=(const Rational& a) const;

  Rational override operator>(const Rational& a) const;

  Rational override operator<(const Rational& a) const;


};
#endif

