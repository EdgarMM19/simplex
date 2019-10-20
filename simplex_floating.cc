#include <bits/stdc++.h>
using namespace std;


using ld = long double;
using vr = vector<ld>;
using vvr = vector<vr>;

const ld INF = 1e9;

vector<ld> calculateR(const vr& c, const vvr& invAb, 
                                const vector<int>& vb, 
                                const vector<int>& vnb, const vvr& A){

    vr r;
    int nb = vnb.size(),m=invAb.size();
    
    // TODO: r = cn - cb * invAb * An
    for(int i = 0; i < nb; ++i) r.push_back(c[vnb[i]]);
    
    vr aux(m, ld(0));
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            aux[i] -= c[vb[j]]*invAb[j][i];
    
    // EXPLAIN: (1,n-m o nb)+(-(1,m)*(m,m))*(m,n-m o nb)
    vr aux2(nb,ld(0));
    for(int i = 0; i < nb; ++i)
        for(int j = 0; j < m; ++j)
            aux2[i] += aux[j]*A[j][vnb[i]];
    
    for(int i = 0; i < nb; ++i)
        r[i] += aux2[i];
    
    return r;
}

vector<ld> calculateD(const vvr& invAb, 
                                int q, const vvr& A){
    // d = -invAb*Aq
    int m = invAb.size();
    vr d(m,ld(0));

    for(int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            d[i] -= invAb[i][j]*A[j][q];

    return d;
}

void recalculateAbinv(vvr& invAb, int p, const vr& d) {
    int m = invAb.size();
    vr E(m);
    for (int i=0; i<m; i++) {
        if (i == p) E[i] = ld(1)/d[p];
        else E[i] = -d[i]/d[p];
    }
    vvr _invAb(m, vr(m));
    for (int i=0; i<m; i++) {
        for (int j=0; j<m; j++) {
            if(i != p) _invAb[i][j] = invAb[i][j] + E[p]*invAb[p][j];
            else _invAb[i][j] = E[p]*invAb[p][j];
        }
    }
    invAb = _invAb;
}

// given a,b,c and an initial x and base st x is a SBF
// minimizes c*x, restricted to a*x = b,
// returns 1 = optimal found, 2 = unbounded problem, 3 = SBF degenerated
int phase2(const vvr& a, vr& x, const vr& b, const vr& c, vector<int>& vb,
            const bool bland, vvr& invAb, int& iter){

    int m = a.size(), n = x.size(), nB = n-m;
    
    vector<int> vnb;
    int itBas = 0;
    for(int i = 0; i < n; ++i){
        if(itBas >= m or vb[itBas] != i)
            vnb.push_back(i);
        else
            itBas++;
    }

    while (++iter) {
        cerr << "Iteracio " << iter << ": \n";
        
        // calcular Ab^-1 un cop i despres updatejar????
        // calcular r
        vr r = calculateR(c, invAb, vb, vnb, a);

        bool optim = true;

        // si r >= 0 acabat
        for(int i = 0; i < nB; ++i)
            if(r[i] < ld(0))
                optim = false;
        if(optim) return 1;

        // seleccionar q dentrada
        // q index real que entra
        int q = -1;
        if(bland){
            // per la regla de bland
            for(int i = 0; i < nB; ++i)
                if(r[i] < ld(0) and (q == -1 or vnb[i] < q))
                    q = vnb[i];
        }
        else{
            // pel minim cost reduit
            for(int i = 0; i < nB; ++i)
                if((q == -1 and r[i] < ld(0)) or (q != -1 and r[i] < r[q]))
                    q = vnb[i];
        }
       
        // calcular d
        vr d = calculateD(invAb, q, a);

        // si Db >= 0 ilimitat acabat
        bool unbounded = true;

        for(int i = 0; i < m; ++i)
            if(d[i] < ld(0)) unbounded = false;
        if(unbounded) return 2;

        // p posicio a la base de la variable que surt
        int p = -1;
        ld theta = INF;
        for(int i = 0; i < m; ++i){
            if(d[i] < ld(0) and ((-x[vb[i]])/d[i] < theta or (-x[vb[i]]/d[i] == theta and vb[i] < vb[p]))){
                theta = -x[vb[i]]/d[i];
                p = i;
            }
        }

        // TODO: si no aplica bland comprovar si estem ciclant???
        // x = x + theta*d;

        x[q] = theta;
        for(int i = 0; i < m; ++i)
            x[vb[i]] += theta*d[i];
        ld sol = 0;
        for (int i=0; i<n; i++) sol += c[i]*x[i];
        cerr << "p: " << p << ", q: " << q << ", theta*: " << theta << ", sol:"<< sol << "x: \n";
        for(int i = 0; i < n; ++i)
            cerr << x[i] << "\n";
        for(int i = 0; i < nB; ++i)
            if(vnb[i] == q)
                vnb[i] = vb[p];
        vb[p] = q;

        // recalcular invAb
        recalculateAbinv(invAb, p, d);
    }
}

// minimizes c*x, restricted to a*x = b,
// returns 1 = optimal found, 2 = unbounded problem, 3 = SBF degenerated, 4 = no factible solution exists
int simplex(const vvr& a, const vr& b, const vr& c, vr& xsol, const bool bland){
    int n = c.size(), m = a.size();
    // iniciar a ampliada,construir nova b
    int iter = 0;
    vr x(n+m, ld(0));
    vr cPhase1(n+m, ld(0));
    vector<int> vbPhase1;
    for(int i = n; i < n+m; ++i) {
        cPhase1[i] = ld(1);
        x[i] = b[i-n];
        vbPhase1.push_back(i);
    }

    vvr invAb(m, vr(m, ld(0)));
    for(int i = 0; i < m; ++i)
        invAb[i][i] = ld(1);

    vvr aPhase1(m, vr(n+m, ld(0)));

    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j)
            aPhase1[i][j] = a[i][j];
        aPhase1[i][i+n] = ld(1);
    }
    for(int i = 0; i < n+m; ++i)
            cerr << x[i] << "\n";
    cerr << "Inici fase 1: \n";
    int resultPhase1 = phase2(aPhase1, x, b, cPhase1, vbPhase1, bland, invAb, iter);

    // comprovar si existeix SBF
    bool factible = true;
    for(int i = n; i < n+m; ++i)
        if(x[i] > ld(0)) factible = false;
    
    if(not factible)
        return 4;

    // cridar phase2 amb la SBF trobada i la a,b,c originals
    xsol = vr(n);
    for(int i = 0; i < n; ++i)
        xsol[i] = x[i];

    cerr << "Inici fase 2: \n";
    return phase2(a, xsol, b, c, vbPhase1, bland, invAb, iter);
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<ld>> A(n, vector<ld>(m));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            int x;
            cin >> x;
            A[i][j] = ld(x);
        }
    }

    vector<ld> B(n);
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        B[i] = ld(x);
    }
    
    vector<ld> C(m);
    for (int i=0; i<m; i++) {
        int x;
        cin >> x;
        C[i] = ld(x);
    }

    vr sol;
    int solFinal = simplex(A, B, C, sol, true);
    
    cout << solFinal << " -> x:" << endl;
    ld ans(0);
    for (int i=0; i<(int)C.size() and i <(int)sol.size(); i++) {
        ans += C[i]*sol[i];
        cerr << sol[i] << endl;
    }
    cout << "opt: " << ans << endl;
}
