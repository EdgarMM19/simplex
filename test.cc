#include<bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;

int main3() {
    Bigint A(1);
    for (int i=1; i<100; i++) {
        A *= Bigint(i);
        cout << i << ": " << A << endl;
    }
    return 0;
}
