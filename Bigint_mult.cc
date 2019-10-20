#include<bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

Bigint Bigint::operator*(Bigint const &N) const {
    if (neg and N.neg) return opposite(*this)*opposite(N);
    if (neg) return opposite(opposite(*this)*N);
    if (N.neg) return opposite((*this)*opposite(N));

    return Bigint(0, __mult__(this->digits, N.digits));
}

Bigint Bigint::operator/(Bigint const &N) const {
    if (neg and N.neg) return opposite(*this)/opposite(N);
    if (neg) return opposite(opposite(*this)/N);
    if (N.neg) return opposite((*this)/opposite(N));

    Bigint U(1);
    Bigint L(0), R(*this);
    while ((R - L) > U) {
        Bigint M = div2(L + R);
        if (N*M > (*this)) R = M;
        else if (N*M == (*this)) return M;
        else L = M;
    }
    if (N*R <= (*this)) return R;
    return L;
}

Bigint Bigint::operator%(Bigint const &N) const {
    Bigint R = (*this)/N;
    return (*this) - R*N;
}

void Bigint::operator*=(Bigint const &N) {
    *this = (*this) * N;
};

void Bigint::operator/=(Bigint const &N) {
    *this = (*this) / N;
};

void Bigint::operator%=(Bigint const &N) {
    *this = (*this) % N;
};