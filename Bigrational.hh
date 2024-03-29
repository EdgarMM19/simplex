#include<bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

class Bigrational {
    private:
    public:
        Bigint NUM, DEN;
        
        Bigrational();
        Bigrational(ll const &a, ll const &b);
        Bigrational(ll const &a);
        Bigrational(Bigint const &A, Bigint const &B);
        Bigrational(Bigint const &A);

        static Bigrational simplify(Bigrational const &A);
        static Bigrational opposite(Bigrational const &A);
        static bool isZero(Bigrational const &A);        

        Bigrational operator+(Bigrational const &N) const;
        Bigrational operator-(Bigrational const &N) const;
        Bigrational operator-() const;
        Bigrational operator*(Bigrational const &N) const;
        Bigrational operator/(Bigrational const &N) const;
        void operator+=(Bigrational const &N);
        void operator-=(Bigrational const &N);
        void operator*=(Bigrational const &N);
        void operator/=(Bigrational const &N);

        bool operator>(Bigrational const &N) const;
        bool operator<(Bigrational const &N) const;
        bool operator==(Bigrational const &N) const;
        bool operator!=(Bigrational const &N) const;
        bool operator>=(Bigrational const &N) const;
        bool operator<=(Bigrational const &N) const;
        
        friend ostream& operator<<(ostream& os, Bigrational const &N);
};
