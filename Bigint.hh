#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
const ll BASE = 1e9;

class Bigint {
    private:
        bool neg;
        vll digits;

        // A and B are positive
        Bigint _sum(Bigint const &A, Bigint const &B) const;
        // A and B are positive and A >= B
        Bigint _minus(Bigint const &A, Bigint const &B) const;
    public:
        Bigint();
        Bigint(ll n);
        Bigint(bool _neg, vll _digits);

        static Bigint div2(Bigint const &A);
        static Bigint opposite(Bigint const &A);
        static bool isZero(Bigint const &A);
        
        Bigint operator+(Bigint const &N) const;
        Bigint operator-(Bigint const &N) const;
        Bigint operator*(Bigint const &N) const;
        Bigint operator/(Bigint const &N) const;
        bool operator>(Bigint const &N) const;
        bool operator<(Bigint const &N) const;
        bool operator==(Bigint const &N) const;
        bool operator>=(Bigint const &N) const;
        bool operator<=(Bigint const &N) const;
        friend ostream& operator<<(ostream& os, Bigint const &N);
};