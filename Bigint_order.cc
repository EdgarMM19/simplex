#include<bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

bool Bigint::operator>(Bigint const &A) const {
    if (isZero(*this) and isZero(A)) return false;
    
    if (neg and A.neg) {
        if (digits.size() > A.digits.size()) return false;
        if (digits.size() < A.digits.size()) return true;

        for (int i=(int)digits.size() - 1; i>=0; i--) {
            if (digits[i] > A.digits[i]) return false;
            if (digits[i] < A.digits[i]) return true;
        }
        return false;
    }
    else if(neg) {
        return false;
    }
    else if(A.neg) {
        return true;
    }
    else {
        if (digits.size() > A.digits.size()) return true;
        if (digits.size() < A.digits.size()) return false;

        for (int i=(int)digits.size() - 1; i>=0; i--) {
            if (digits[i] > A.digits[i]) return true;
            if (digits[i] < A.digits[i]) return false;
        }
        return false;
    }
}

bool Bigint::operator<(Bigint const &A) const {
    return A > *this;
}

bool Bigint::operator==(Bigint const &A) const {
    return not ((*this > A) or (*this < A));
}

bool Bigint::operator!=(Bigint const &A) const {
    return not (*this == A);
}

bool Bigint::operator<=(Bigint const &A) const {
    return not (*this > A);
}

bool Bigint::operator>=(Bigint const &A) const {
    return not (*this < A);
}