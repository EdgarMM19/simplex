#include<bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

Bigint Bigint::_sum(Bigint const &A, Bigint const &B) const {
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

Bigint Bigint::_minus(Bigint const &A, Bigint const &B) const {
    if (A == B) {
        return Bigint(0);
    }
    else if (B > A) {
        return opposite(_minus(B, A));
    }
    
    Bigint S;
    ll carry = 0;
    int it = 0;
    while (it < (int)B.digits.size()) {
        if (A.digits[it] >= B.digits[it] + carry) {
            S.digits.push_back(A.digits[it] - B.digits[it] - carry);
            carry = 0;
        }
        else {
            S.digits.push_back(BASE + A.digits[it] - B.digits[it] - carry);
            carry = 1;
        }
        it++;
    }
    while (it < (int)A.digits.size()) {
        if (A.digits[it] >= carry) {
            S.digits.push_back(A.digits[it] - carry);
            carry = 0;
        }
        else {
            S.digits.push_back(BASE + A.digits[it] - carry);
            carry = 1;       
        }
        it++;
    }
    while (S.digits.back() == 0) {
        S.digits.pop_back();
    }
    return S;
}

Bigint Bigint::operator+(Bigint const &N) const {
    if (neg and N.neg) {
        return opposite(opposite(*this) + opposite(N));
    } 
    else if (neg) {
        return _minus(N, opposite(*this));
    }
    else if (N.neg) {
        return _minus(*this, opposite(N));
    }
    else {
        return _sum(*this, N);
    }
}

Bigint Bigint::operator-(Bigint const &N) const {
    return *this + opposite(N);
}