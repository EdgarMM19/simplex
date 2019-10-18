#include<bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;

bool Bigrational::operator>(Bigrational const &A) const {
    if (this->DEN.neg and A.DEN.neg) return this->NUM*A.DEN > this->DEN*A.NUM;
    if (this->DEN.neg or A.DEN.neg) return this->NUM*A.DEN < this->DEN*A.NUM;
    return this->NUM*A.DEN > this->DEN*A.NUM;
}

bool Bigrational::operator<(Bigrational const &A) const {
    return A > *this;
}

bool Bigrational::operator==(Bigrational const &A) const {
    return not ((*this > A) or (*this < A));
}

bool Bigrational::operator!=(Bigrational const &A) const {
    return not (*this == A);
}

bool Bigrational::operator<=(Bigrational const &A) const {
    return not (*this > A);
}

bool Bigrational::operator>=(Bigrational const &A) const {
    return not (*this < A);
}