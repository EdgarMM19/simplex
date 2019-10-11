#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
const ll BASE = 10;

class Bigint {
    private:
        bool neg;
        vll digits;

        // A and B are positive
        Bigint _sum(Bigint const &A, Bigint const &B);
        // A and B are positive and A >= B
        Bigint _minus(Bigint const &A, Bigint const &B);

    public:
        Bigint();
        Bigint(ll n);
        Bigint(bool _neg, vll _digits);

        Bigint operator+(Bigint const &N);
        Bigint operator-(Bigint const &N);
        bool operator>(Bigint const &N);
        friend ostream& operator<<(ostream& os, Bigint const &N);
};