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
int phase2(const vvr& a, vvr& x,const vvr& b,const vvr& c, vector<int>& vb,const bool bland){


    //iteracions while true

        //calcular r, calcular d
        //si r >= 0 acabat

        //seleccionar q dentrada
        //si Db >= 0 ilimitat acabat

        //si no aplica bland comprovar si estem ciclant???

}


//given a,b,c 



//to check? 
//b>=0 ??????????




//minimizes c*x, restricted to a*x = b,
//returns 1 = optimal found, 2 = unbounded problem, 3 = SBF degenerated, 4 = no factible solution exists
int simplex(const vvr& a,const vvr& b,const vvr& c, vvr& xsol,const bool bland){

    int n = c.size(), m = a.size();
    //iniciar a ampliada,construir nova b

    //cridar phase2 x resoldre fase 1
    vr x(n+m,Bigrational(0));
    vr cPhase1(n+m,Bigrational(0));
    vector<int> vbPhase1;
    for(int i = n; i < n+m; ++i) {
        cPhase1[i]=x[i]=Bigrational(1);
        vb.push_back(i);
    }
    vvr aPhase1(m,vr(n+m,Bigrational(0)));
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j)
            aPhase1[i][j] = a[i][j];
        aPhase1[i][i+n] = Bigrational(1);
    }
    int resultPhase1 = phase2(aPhase1,x,b,cPhase1,vb,bland);

    //comprovar si existeix SBF
    bool factible = true;
    for(int i = n; i < n+m; ++i)
        if(x[i] > EPS)
            factible = false;
    if(not factible)
        return 4;

    //cridar phase2 amb la SBF trobada i la a,b,c originals
    xsol = vr(n);
    for(int i = 0; i < n; ++i)
        xsol[i] = x[i];
    return phase2(a,xsol,b,c,vb,bland);
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
