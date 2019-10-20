#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;
// BASE tiene que ser par
const ll BASE = 1e9;

class Bigint {
    private:
    public:
        struct comp {
            ld r, c;
        };
        static comp cmult(comp a, comp b);
        static ll creverse(ll a, ll p);
        static vector <comp> fft(vector <comp>v, ll m, ll p);
        static vector <comp> ifft(vector <comp>v, ll m, ll p);
        static vll __mult__(const vll& s, const vll& t);
            
        // A and B are positive
        Bigint _sum(Bigint const &A, Bigint const &B) const;
        // A and B are positive and A >= B
        Bigint _minus(Bigint const &A, Bigint const &B) const;
        bool neg;
        vll digits;

        Bigint();
        Bigint(ll n);
        Bigint(bool _neg, vll _digits);

        static Bigint div2(Bigint const &A);
        static Bigint opposite(Bigint const &A);
        static Bigint gcd(Bigint const &A, Bigint const &B);
        static bool isZero(Bigint const &A);

        Bigint operator+(Bigint const &N) const;
        Bigint operator-() const;
        Bigint operator-(Bigint const &N) const;
        Bigint operator*(Bigint const &N) const;
        Bigint operator/(Bigint const &N) const;
        Bigint operator%(Bigint const &N) const;
        void operator+=(Bigint const &N);
        void operator-=(Bigint const &N);
        void operator*=(Bigint const &N);
        void operator/=(Bigint const &N);
        void operator%=(Bigint const &N);

        bool operator>(Bigint const &N) const;
        bool operator<(Bigint const &N) const;
        bool operator==(Bigint const &N) const;
        bool operator!=(Bigint const &N) const;
        bool operator>=(Bigint const &N) const;
        bool operator<=(Bigint const &N) const;
        
        friend ostream& operator<<(ostream& os, Bigint const &N);
};