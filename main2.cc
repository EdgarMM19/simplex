#include <bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;

const Bigrational INF(1,0);

using vr = vector<Bigrational>;
using vvr = vector<vr>;


//given a,b,c and an initial x and base st x is a SBF
//minimizes c*x, restricted to a*x = b,
//returns 1 = optimal found, 2 = unbounded problem, 3 = SBF degenerated
int phase2(const vvr& a, vvr& x,const vvr& b,const vvr& c, vector<int>& vb,const bool bland,vvr invAb){

    int m = a.size(), n = x.size(), nB = n-m;
    
    vector<int> vnb;
    int itBas = 0;
    for(int i = 0; i < n; ++i){
        if(itBas >= m or vb[itBas] != i)
            vnb.push_back(i);
        else
            itBas++;
    }

    for(int iteration = 1;;iteration++){


        //calcular Ab^-1 un cop i despres updatejar????
         //calcular r
        vr r;
        for(int i = 0; i < nB; ++i)
            r.push_back(c[vnb[i]]);
        //no implementado:
        // r -= cb * invAb * An

        bool optim = true;


        //si r >= 0 acabat

        for(int i = 0; i < nB; ++i)
            if(r[i] < Bigrational(0))
                optim = false;

        if(optim)
            return 1;


        //seleccionar q dentrada

        int q = -1;
        if(bland){
            for(int i = 0; i < nB; ++i)
                if(r[i] < Bigrational(0) and (q == -1 or vnb[i] < q))
                    q = i;
        }
        else{
            for(int i = 0; i < nB; ++i)
                if((q == -1 and r[i] < Bigrational(0)) or (q != -1 and r[i] < -r[q]))
                    q = i;
        }
       
        //calcular d
        vr d;
        //vr d = -invAb*Aq

        //si Db >= 0 ilimitat acabat
        bool unbounded = true;

        for(int i = 0; i < m; ++i){
            if(d[i] < Bigrational(0))
                unbounded = false;
        }
        if(unbounded)
            return 2;

        int p = -1;
        int theta = INF;
        for(int i = 0; i < m; ++i){
            if(d[vb[i]] < Bigrational(0) and (-x[vb[i]]/d[vb[i]] < theta or (-x[vb[i]]/d[vb[i]] == theta and vb[i] < vb[p]))){
                theta = -x[vb[i]]/d[vb[i]];
                p = i;
            }
        }

        // si no aplica bland comprovar si estem ciclant???
        // x = x + theta*d;
        // 
        for(int i = 0; i < nb; ++i)
            if(vnb[i] == q)
                vnb[i] = p;
        vb[p] = q;
        //recalcular invAb




    }

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
    vvr invAb(m,vr(m,Bigrational(0)));
    for(int i = 0; i < m; ++i)
        invAb[i][i] = Bigrational(1);
    vvr aPhase1(m,vr(n+m,Bigrational(0)));
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j)
            aPhase1[i][j] = a[i][j];
        aPhase1[i][i+n] = Bigrational(1);
    }
    cerr << "Inici fase 1: \n";

    int resultPhase1 = phase2(aPhase1,x,b,cPhase1,vb,bland,invAb);

    //comprovar si existeix SBF
    bool factible = true;
    for(int i = n; i < n+m; ++i)
        if(x[i] > Bigrational(0))
            factible = false;
    if(not factible)
        return 4;

    //cridar phase2 amb la SBF trobada i la a,b,c originals
    xsol = vr(n);
    for(int i = 0; i < n; ++i)
        xsol[i] = x[i];

    cerr << "Inici fase 2: \n";
    return phase2(a,xsol,b,c,vb,bland,invAb);
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
