#include <bits/stdc++.h>
#include "Bigrational.hh"
using namespace std;

const Bigrational EPS(1, 1e9);
const Bigrational INF(1e9, 1);

void pivot(vector<vector<Bigrational>>& A, vector<Bigrational>& b,
            int n, int m, int bi, int nv) {
    Bigrational pd = A[bi][nv];
    for (int j=0; j<n+m; j++) A[bi][j] /= pd;
    b[bi] /= pd;
    for (int i=0; i<m+2; i++) {
        if (i == bi)
            continue;
        Bigrational pn = A[i][nv];
        for (int j=0; j<n+m; j++) A[i][j] -= A[bi][j] * pn;
        b[i] -= b[bi] * pn;
    }
}

Bigrational fabsl(Bigrational const& A) {
    int a = A.NUM.neg;
    int b = A.DEN.neg;
    if ((a and b) or (!a and !b))
        return A;
    else
        return Bigrational::opposite(A);
}

void reinvert(vector<vector<Bigrational> >& A, vector<Bigrational>& b,
                int n, int m, vector<int>& bx) {
    for (int i=0; i<m; i++) {
        int mxpivot = i;
        for (int ii=i+1; ii<m; ii++) {
            if (fabsl(A[i][bx[ii]]) > fabsl(A[i][bx[mxpivot]])) mxpivot = ii;
        }
        swap(bx[i], bx[mxpivot]);
        pivot(A, b, n, m, i, bx[i]);
    }
}

// min c^Tx, subj Ax=b, x>=0
vector<Bigrational> simplex(vector<vector<Bigrational> > A,
                            vector<Bigrational> b, vector<Bigrational> c) {
    const int n = c.size(), m = b.size(); //n var, m eq
    // make b positive
    for (int i=0; i<m; i++) {
        if (b[i] < Bigrational(0)) {
            for (int j=0; j<n; j++) A[i][j] *= Bigrational(-1);
            b[i] *= Bigrational(-1);
        }
    }
    // list of base/independent variable ids
    vector<int> bx(m), nx(n);
    for (int i=0; i<m; i++) bx[i] = n + i; // aux in base
    for (int i=0; i<n; i++) nx[i] = i; // real independent
    // extend A, b
    A.resize(m + 2);
    for (int i=0; i<m+2; i++) A[i].resize(n + m, Bigrational(0)); // aux vars
    for (int i=0; i<m; i++) A[i][n + i] = Bigrational(1); // aux vars
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) A[m][j] = A[m][j] + A[i][j]; // row m is phase 0 costs
    }
    b.push_back(accumulate(b.begin(), b.end(), Bigrational(0))); // row m is phase 0 costs
    for (int j=0; j<n; j++) A[m + 1][j] = -c[j]; // row m+1 is costs
    for (int i=0; i<m; i++) A[m + 1][n + i] = -INF; // aux costs
    b.push_back(Bigrational(0));
    vector<vector<Bigrational> > A_(A);
    vector<Bigrational> b_(b);
    vector<Bigint> forbidden(n + m, false);
    // main optimization
    for (int phase=0; phase<2; phase++) {
        for (int nsteps = 0;; ++nsteps) {
            cerr << "Fase: " << phase+1 << ", iter:" << nsteps+1 << "\n";
            // select an independent variable to enter
            int ni = -1;
            for (int i=0; i<n; i++) {
                if (Bigint::isZero(forbidden[nx[i]]) 
                    && A[m][nx[i]] > EPS 
                    && (ni < 0 || nx[i] < nx[ni])) ni = i;
            }
            if (ni == -1) break;
            int nv = nx[ni];
            // select a base variable to leave
            vector<Bigrational> bound(m);
            for (int i=0; i<m; i++) {
                bound[i] = (A[i][nv] < EPS ? INF : b[i] / A[i][nv]);
            }
            if (!(*min_element(bound.begin(), bound.end()) < INF))
                return vector<Bigrational>(n, INF); // unbounded
            int bi = 0;
            for (int i=0; i<m; i++) {
                if (bound[i] < bound[bi] - EPS
                    || (bound[i] < bound[bi] + EPS && bx[i] < bx[bi]))
                        bi = i;
            }
            // update
            swap(nx[ni], bx[bi]);
            if (false && nsteps % 100 == 0) {
                A = A_;
                b = b_;
                reinvert(A, b, n, m, bx);
            }
            else
                pivot(A, b, n, m, bi, nv);
        }
        if (phase == 0) {
            if (b[m] > EPS) return vector<Bigrational>(); // no solution
            for (int i=0; i<n+m; i++) {
                if (i >= n || A[m][i] < -EPS) forbidden[i] = true;
            }
            swap(A[m], A[m + 1]);
            swap(b[m], b[m + 1]);
            swap(A_[m], A_[m + 1]);
            swap(b_[m], b_[m + 1]);
        }
    }
    vector<Bigrational> x(n + m, Bigrational(0, 1));
    for (int i=0; i<m; i++) x[bx[i]] = b[i];
    x.resize(n);
    return x;
}
/*
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
}*/
