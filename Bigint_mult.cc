#include<bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

Bigint Bigint::operator*(Bigint const &N) const {
    if (neg and N.neg) return opposite(*this)*opposite(N);
    if (neg) return opposite(opposite(*this)*N);
    if (N.neg) return opposite((*this)*opposite(N));

    Bigint R(0);
    if (isZero(*this) or isZero(N)) return R;

    for (int i=0; i<(int)digits.size(); i++) {
        Bigint T;
        for (int j=0; j<i; j++) T.digits.push_back(0LL);
        ll c = 0;
        for (int j=0; j<(int)N.digits.size(); j++) {
            ll d = digits[i]*N.digits[j] + c;
            T.digits.push_back(d%BASE);
            c = d/BASE;
        }
        if (c != 0) T.digits.push_back(c);
        R = R + T;
    }
    return R;
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