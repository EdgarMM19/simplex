#include<bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

Bigint::Bigint() {
    neg = false;
    digits = vll();
}

Bigint::Bigint(ll n) {
    if (n < 0) neg = true, n *= -1;
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

Bigint Bigint::_sum(Bigint const &A, Bigint const &B) {
    Bigint S;
    ll carry = 0;
    int it = 0;
    while (it<(int)min(A.digits.size(), B.digits.size())) {
        ll sumand = (A.digits[it] + B.digits[it] + carry);
        S.digits.push_back(sumand%BASE);
        carry = sumand/BASE;
        ++it;
    }
    if (it == A.digits.size()) {
        while (it < (int)B.digits.size()) {
            ll sumand = B.digits[it] + carry;
            S.digits.push_back(sumand%BASE);
            carry = sumand/BASE;
            it++;
        }
        if (carry != 0) S.digits.push_back(carry);
    }
    else if (it == B.digits.size()) {
        while (it < (int)A.digits.size()) {
            ll sumand = A.digits[it] + carry;
            S.digits.push_back(sumand%BASE);
            carry = sumand/BASE;
            it++;
        }
        if (carry != 0) S.digits.push_back(carry);
    }
    return S;
}

Bigint Bigint::_minus(Bigint const &A, Bigint const &B) {
    // TODO(jlcontreras): implement
}

Bigint Bigint::operator+(Bigint const &N) {
    if (neg and N.neg) {
        Bigint _A(0, digits);
        Bigint _B(0, N.digits);
        Bigint M = _sum(_A, _B);
        M.neg = true;
        return M;
    } 
    else if (neg) {
        Bigint _A(0, digits);
        if (_A > N) {
            return _minus(_A, N);
        }
        else {
            Bigint M = _minus(N, _A);
            M.neg ^= 1;
            return M;
        }
    }
    else if (N.neg) {
        Bigint _A(0, digits);
        Bigint _B(0, digits);
        if (_A > _B) {
            return _minus(_A, _B);
        }
        else {
            Bigint M = _minus(_B, _A);
            M.neg ^= 1;
            return M;
        }
    }
    else {
        Bigint _A(0, digits);
        return _sum(_A, N);
    }
}

Bigint Bigint::operator-(Bigint const &N) {
    if (neg and N.neg) {
        Bigint _A(0, digits);
        Bigint _B(0, N.digits);
        if (_B > _A) {
            return _minus(_B, _A);
        }
        else {
            Bigint M = _minus(_A, _B);
            M.neg ^= 1;
            return M;
        }
    }
    else if (neg) {
        Bigint _A(0, digits);
        Bigint M = _sum(_A, N);
        M.neg = true;
        return M;
    }
    else if (N.neg) {
        Bigint _A(0, digits);
        Bigint _B(0, N.digits);
        return _sum(_A, _B);
    }
    else {
        Bigint _A(0, N.digits);
        if (_A > N) {
            return _minus(_A, N);
        }
        else {
            Bigint M = _minus(N, _A);
            M.neg ^= 1;
            return M;
        }
    }
}

bool Bigint::operator>(Bigint const &A) {
    if (digits.size() > A.digits.size()) return true;
    if (digits.size() < A.digits.size()) return false;

    for (int i=(int)digits.size() - 1; i>=0; i--) {
        if (digits[i] > A.digits[i]) return true;
        if (digits[i] < A.digits[i]) return false;
    }
    return false;
}

ostream& operator<<(ostream& os, Bigint const &M) {
    if (M.neg) os << "-";
    for (int i=(int)M.digits.size()-1; i>=0; i--) os << M.digits[i];
    return os;
}