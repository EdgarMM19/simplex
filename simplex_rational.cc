#include <bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;

#define DEBUG(cnt) {cerr << #cnt << ": "; for(auto vrb : cnt) cerr << vrb << ", "; cerr << endl;}

using vr = vector<Bigrational>;
using vvr = vector<vr>;

const Bigrational INF = Bigrational(1, 0);

vector<Bigrational> calculateR(const vr& c, const vvr& invAb, 
                                const vector<int>& vb, 
                                const vector<int>& vnb, const vvr& A){

    vr r;
    int nb = vnb.size(), m = invAb.size();
    
    // TODO: r = cn - cb * invAb * An
    for(int i = 0; i < nb; ++i) r.push_back(c[vnb[i]]);
    cerr << "    r inicialitzat" << endl;
    vr aux(m, Bigrational(0));
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            aux[i] -= c[vb[j]]*invAb[j][i];
    cerr << "    aux calculat" << endl; 
    
    // EXPLAIN: (1,n-m o nb)+(-(1,m)*(m,m))*(m,n-m o nb)
    vr aux2(nb,Bigrational(0));
    for(int i = 0; i < nb; ++i)
        for(int j = 0; j < m; ++j)
            aux2[i] += aux[j]*A[j][vnb[i]];
    cerr << "    aux2 calculat" << endl;
    for(int i = 0; i < nb; ++i)
        r[i] += aux2[i];
    cerr << "    r finito" << endl;
    return r;
}

vector<Bigrational> calculateD(const vvr& invAb, 
                                int q, const vvr& A){
    // d = -invAb*Aq
    int m = invAb.size();
    vr d(m,Bigrational(0));

    for(int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            d[i] -= invAb[i][j]*A[j][q];

    return d;
}

void recalculateAbinv(vvr& invAb, int p, const vr& d) {
    int m = invAb.size();
    vr E(m);
    for (int i=0; i<m; i++) {
        E[i] = -d[i]/d[p];
    }
    E[p] = Bigrational(-1.0)/d[p] - Bigrational(1);
    cerr << "    E trobat" << endl;
    vr L = invAb[p];
    cerr << "    L copiat" << endl;
    for (int i=0; i<m; i++) {
        for (int j=0; j<m; j++) {
            invAb[i][j] += E[i]*L[j];
        }
    }
}

// given a,b,c and an initial x and base st x is a SBF
// minimizes c*x, restricted to a*x = b,
// returns 1 = optimal found, 2 = unbounded problem, 3 = SBF degenerated
int phase2(const vvr& a, vr& x, const vr& b, const vr& c,
            vector<int>& vb, vector<int>& vnb,
            const bool bland, vvr& invAb, int& iter){

    int m = a.size(), n = x.size(), nB = n-m;
    set<vector<int>> cicle; 
    while (++iter) {
        // calcular Ab^-1 un cop i despres updatejar????
        // calcular r
        vr r = calculateR(c, invAb, vb, vnb, a);
        cerr << "R calculat" << endl;

        bool optim = true;

        // si r >= 0 acabat
        for(int i = 0; i < nB; ++i)
            if(r[i] < Bigrational(0))
                optim = false;
        if(optim) return 1;
        cerr << "Es optim? fet" << endl;
        // seleccionar q dentrada
        // q index real que entra
        int q = -1;
        Bigrational rq(0);
        if(bland){
            // per la regla de bland
            for(int i = 0; i < nB; ++i)
                if(r[i] < Bigrational(0) and (q == -1 or vnb[i] < q)){
                    q = vnb[i];
                    rq = r[i];
                }
        }
        else{
            // pel minim cost reduit
            for(int i = 0; i < nB; ++i)
                if((q == -1 and r[i] < Bigrational(0)) or (q != -1 and r[i] < r[q])){
                    q = vnb[i];
                    
                    rq = r[i];
                }
            if(cicle.count(vb) == 1)
                return 3;
            cicle.insert(vb);
        }
        cerr << "Q trobada!" << endl;
       
        // calcular d
        vr d = calculateD(invAb, q, a);
        cerr << "D calculada!" << endl;
        
        // si Db >= 0 ilimitat acabat
        bool unbounded = true;

        for(int i = 0; i < m; ++i)
            if(d[i] < Bigrational(0)) unbounded = false;
        if(unbounded) return 2;
        cerr << "Es illimitat? fet" << endl;
        
        // p posicio a la base de la variable que surt
        int p = -1;
        Bigrational theta = INF;
        for(int i = 0; i < m; ++i){
            if(d[i] < Bigrational(0) and ((-x[vb[i]])/d[i] < theta or (-x[vb[i]]/d[i] == theta and vb[i] < vb[p]))){
                theta = -x[vb[i]]/d[i];
                p = i;
            }
        }
        cerr << "p i theta trobats" << endl;
        // TODO: si no aplica bland comprovar si estem ciclant???
        // x = x + theta*d;
        for(int i = 0; i < m; ++i)
            x[vb[i]] += theta*d[i];
        x[q] = theta;

        Bigrational sol = 0;
        for (int i=0; i<n; i++) sol += c[i]*x[i];
        
        cout << "Iteracio " << iter << ": \n";
        cout << "q: " << q+1 << ", rq = " << rq << ", B(p): " << vb[p]+1 <<  ", theta*: " << theta << ", z: "<< sol << "\n";
    
        for(int i = 0; i < nB; ++i)
            if(vnb[i] == q)
                vnb[i] = vb[p];
        vb[p] = q;
        cerr << endl;
        

        // recalcular invAb
        recalculateAbinv(invAb, p, d);
        cerr << "inversa recalculada" << endl;
    }
}

// minimizes c*x, restricted to a*x = b,
// returns 1 = optimal found, 2 = unbounded problem, 3 = SBF degenerated, 4 = no factible solution exists
int simplex(const vvr& a, const vr& b, const vr& c, vr& xsol, const bool bland){
    int n = c.size(), m = a.size();
    // iniciar a ampliada,construir nova b
    int iter = 0;
    vr x(n+m, Bigrational(0));
    vr cPhase1(n+m, Bigrational(0));
    vector<int> vbPhase1;
    vector<int> vnbPhase1;
    for(int i = n; i < n+m; ++i) {
        cPhase1[i] = Bigrational(1);
        x[i] = b[i-n];
        vbPhase1.push_back(i);
    }
    for (int i=0; i<n; i++)
        vnbPhase1.push_back(i);

    vvr invAb(m, vr(m, Bigrational(0)));
    for(int i = 0; i < m; ++i)
        invAb[i][i] = Bigrational(1);

    vvr aPhase1(m, vr(n+m, Bigrational(0)));

    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j)
            aPhase1[i][j] = a[i][j];
        aPhase1[i][i+n] = Bigrational(1);
    }
    cerr << "Inici fase 1: \n";
    int resultPhase1 = phase2(aPhase1, x, b, cPhase1, vbPhase1, vnbPhase1, bland, invAb, iter);
    
    // eliminem les variables extres
    sort(vnbPhase1.begin(), vnbPhase1.end());
    for (int i=0; i<m; i++) vnbPhase1.pop_back();

    // comprovar si existeix SBF
    bool factible = true;
    for(int i = n; i < n+m; ++i)
        if(x[i] > Bigrational(0)) factible = false;
    
    if(not factible)
        return 4;

    // cridar phase2 amb la SBF trobada i la a,b,c originals
    xsol = vr(n);
    for(int i = 0; i < n; ++i)
        xsol[i] = x[i];

    cerr << "Inici fase 2: \n";
    int solKind = phase2(a, xsol, b, c, vbPhase1, vnbPhase1, bland, invAb, iter);
    if (solKind == 1){
        cout << "An optimal solution has been found:" << endl;
        cout << "VB*:" << endl;
        for(int i = 0; i < vbPhase1.size(); ++i)
            cout << " " << vbPhase1[i]+1;
        cout << endl;
        cout << "VNB*:" << endl;
        for(int i = 0; i < vnbPhase1.size(); ++i)
            cout << " " << vnbPhase1[i]+1;
        cout << endl;
        cout << "x*:" << endl;
        Bigrational ans(0);
        for (int i=0; i<(int)c.size() and i <(int)xsol.size(); i++) {
            ans += c[i]*xsol[i];
            cout << "    " << xsol[i] << endl;
        }
        cout << "z*: " << ans << endl;
        
    }
    return solKind;
    
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<Bigrational>> A(n, vector<Bigrational>(m));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            int x;
            cin >> x;
            A[i][j] = Bigrational(x);
        }
    }

    vector<Bigrational> B(n);
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        B[i] = Bigrational(x);
    }
    
    vector<Bigrational> C(m);
    for (int i=0; i<m; i++) {
        int x;
        cin >> x;
        C[i] = Bigrational(x);
    }

    vr sol;
    // returns 1 = optimal found, 2 = unbounded problem, 3 = SBF degenerated, 4 = no factible solution exists
    int solFinal = simplex(A, B, C, sol, true);
    if(solFinal == 2)
        cout << "The problem is unbounded" << endl;
    else if(solFinal == 3)
        cout << "The problem is degenerated" << endl;
    else if(solFinal == 4)
        cout << "The are not factible solutions" << endl;
}
