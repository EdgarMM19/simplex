
#ifndef _RATIONAL_
#define _RATIONAL_
#include <iostream>


/*
 * Clase Matrix
 */

class Rational {


private:

  long long den,num;
  int _gcd();
  void simplify();

public:

  
  Rational();
  Rational(int a,int b);  
  Rational operator+(const Rational& a) const;

  Rational operator* (const Rational& a) const;
  Rational  operator-(const Rational& a) const;
  Rational  operator/(const Rational& a) const;

  Rational  operator==(const Rational& a) const;
  Rational  operator!=(const Rational& a) const;

  Rational  operator>(const Rational& a) const;

  Rational operator<(const Rational& a) const;


};
#endif

