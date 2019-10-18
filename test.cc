#include<bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;

int main() {
    Bigint A(1);
    Bigrational R(1, 1);
    for (int i=1; i<100; i++) {
        A *= Bigint(i);
        Bigrational Z = Bigrational(Bigint(1), A);
        R += Z;
        cout << i << ": " << R << endl;
    }
}
