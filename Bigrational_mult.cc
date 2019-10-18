#include<bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;

Bigrational Bigrational::operator*(Bigrational const &N) const {
    Bigrational R;
    R.NUM = (*this).NUM*N.NUM;
    R.DEN = N.DEN*(*this).DEN;
    return simplify(R);
}

Bigrational Bigrational::operator/(Bigrational const &N) const {
    Bigrational R;
    R.NUM = (*this).NUM*N.DEN;
    R.DEN = N.NUM*(*this).DEN;
    return simplify(R);
}

void Bigrational::operator*=(Bigrational const &N) {
    *this = (*this) * N;
}

void Bigrational::operator/=(Bigrational const &N) {
    *this = (*this) / N;
}