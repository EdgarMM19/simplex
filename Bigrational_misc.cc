#include<bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;


Bigrational::Bigrational() {
    NUM = DEN = Bigint();
}

Bigrational::Bigrational(ll const &a, ll const &b) {
    (*this) = Bigrational(Bigint(a), Bigint(b));
}


Bigrational::Bigrational(Bigint const &A) {
    NUM = A;
    DEN = Bigint(1);
}
Bigrational::Bigrational(Bigint const &A, Bigint const &B) {
    NUM = A;
    DEN = B;
    if (Bigint::gcd(NUM, DEN) == 1) {}
    else if (Bigint::gcd(NUM, DEN) == -1) {
        NUM = Bigint::opposite(NUM);
        DEN = Bigint::opposite(DEN);
    }
    else {
        Bigrational A = simplify(*this);
        *this = A;
    }
}

Bigrational Bigrational::opposite(Bigrational const &A) {
    return Bigrational(Bigint::opposite(A.NUM), A.DEN);
};

Bigrational Bigrational::simplify(Bigrational const &A) {
    Bigint G = Bigint::gcd(A.NUM, A.DEN);
    return Bigrational(A.NUM/G, A.DEN/G);
};

bool Bigrational::isZero(Bigrational const &A) {
    return Bigint::isZero(A.NUM);
}

ostream& operator<<(ostream& os, Bigrational const &M) {
    os << M.NUM << "/" << M.DEN;
    return os;
}
