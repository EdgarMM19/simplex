#include<bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

int main() {
    Bigint A(-912134);
    Bigint B(-96);
    cout << A << " + " << B << " = " << A+B<< endl;
    A = Bigint(912134);
    B = Bigint(96);
    cout << A << " + " << B << " = " << A+B<< endl;

    A = Bigint(-912134);
    B = Bigint(96);
    cout << A << " - " << B << " = " << A-B<< endl;
    A = Bigint(912134);
    B = Bigint(-96);
    cout << A << " - " << B << " = " << A-B << endl;
}