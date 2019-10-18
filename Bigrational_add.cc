#include<bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;

Bigrational Bigrational::operator+(Bigrational const &N) const {
    Bigrational R;
    R.NUM = N.DEN*(*this).NUM + N.NUM*(*this).DEN;
    R.DEN = N.DEN*(*this).DEN;
    return simplify(R);
}

Bigrational Bigrational::operator-(Bigrational const &N) const {
    return *this + opposite(N);
}

void Bigrational::operator+=(Bigrational const &N) {
    *this = (*this) + N;
}

void Bigrational::operator-=(Bigrational const &N) {
    *this = (*this) - N;
}