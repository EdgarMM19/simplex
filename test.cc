#include<bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

int main() {
    int a, b;
    while (1) {
        a = rand() - 10000;
        b = rand() - 10000;
        if (b == 0) continue;
        Bigint A(a);
        Bigint B(b);
        Bigint C(a*b);
        cout << a << " " << b << endl;
        if (A*B == C) {}
        else {
            cout << A*B << " " << C << endl;
            break; 
        }
    }
}
