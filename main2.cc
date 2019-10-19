#include <bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;

const Bigrational EPS(1, 1e9);
const Bigrational INF(1e9);

using vr = vector<Bigrational>;
using vvr = vector<vr>;


//given a,b,c and an initial x and base st x is a SBF
//minimizes c*x, restricted to a*x = b,
//returns 1 = optimal found, 2 = unbounded problem, 3 = SBF degenerated
int phase2(vvr& a, vvr& x, vvr& b, vvr& c, vr& vb, bool bland){


    //iteracions while true

        //calcular r, calcular d
        //si r >= 0 acabat

        //seleccionar q dentrada
        //si Db >= 0 ilimitat acabat

        //si no aplica bland comprovar si estem ciclant???

}


//given a,b,c
//minimizes c*x, restricted to a*x = b,
//returns 1 = optimal found, 2 = unbounded problem, 3 = SBF degenerated, 4 = no factible solution exists
int simplex(vvr& a, vvr& b, vvr& c, vvr& xsol, bool bland){


    //iniciar a ampliada,construir nova b

    //cridar phase2 x resoldre fase 1

    //comprovar si existeix SBF

    //cridar phase2 amb la SBF trobada i la a,b,c originals

    //resultat
    
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<Bigrational>> A(n, vector<Bigrational>(m));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            int x;
            cin >> x;

            A[i][j] = Bigrational(x, 1);
        }
    }

    vector<Bigrational> B(n);
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        B[i] = Bigrational(x, 1);
    }
    
    vector<Bigrational> C(m);
    for (int i=0; i<m; i++) {
        int x;
        cin >> x;
        C[i] = Bigrational(x, 1);
    }

    vector<Bigrational> sol = simplex(A, B, C);
    Bigrational ans(0, 1);
    for (int i=0; i<(int)C.size(); i++) {
        cout << sol[i] << endl;
        ans += C[i]*sol[i];
    }
    cout << "opt: " << ans << endl;
}
