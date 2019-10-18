#include<bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

Bigint::Bigint() {
    neg = false;
    digits = vll();
}

Bigint::Bigint(ll n) {
    if (n == 0) {
        neg = false, digits.push_back(0);
        return;
    }
    else if (n < 0) neg = true, n *= -1;
    else neg = false;

    digits = vll();
    while (n) {
        digits.push_back(n%BASE);
        n /= BASE;
    }
}

Bigint::Bigint(bool _neg, vll _digits) {
    neg = _neg;
    digits = _digits;
}

Bigint Bigint::opposite(Bigint const &A) {
    return Bigint(A.neg^1, A.digits);
};

Bigint Bigint::gcd(Bigint const &A, Bigint const &B) {
    if (isZero(B)) return A;
    else return gcd(B, A%B);
};

Bigint Bigint::div2(Bigint const &A) {
    if (A.neg) return opposite(div2(opposite(A)));
    if (isZero(A)) return 0;

    int c = 0;
    Bigint S;
    for (int i=(int)A.digits.size()-1; i>=0; i--) {
        S.digits.push_back(A.digits[i]/2 + c);
        if (A.digits[i]%2 == 1) c = BASE/2;
        else c = 0;
    }
    reverse(S.digits.begin(), S.digits.end());
    while (S.digits.back() == 0 and S.digits.size() >= 2) {
        S.digits.pop_back();
    }
    return S;
}

bool Bigint::isZero(Bigint const &A) {
    if (A.digits.size() == 1 and A.digits[0] == 0) return 1;
    else return 0;
}

ostream& operator<<(ostream& os, Bigint const &M) {
    if (Bigint::isZero(M)) {
        os << 0;
    }
    else {
        if (M.neg) os << "-";
        for (int i=(int)M.digits.size()-1; i>=0; i--) os << M.digits[i];
    }
    return os;
}