#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

typedef vector<double> vd;
const double eps = 1e-12;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
    int n = sz(A), m = sz(x), rank = 0, br, bc;
    if (n) assert(sz(A[0]) == m);
    vi col(m); iota(all(col), 0);

    rep(i,n) {
        double v, bv = 0;
        repp(r,i,n) repp(c,i,m)
            if ((v = fabs(A[r][c])) > bv)
                br = r, bc = c, bv = v;
        if (bv <= eps) {
                repp(j,i,n) if (fabs(b[j]) > eps) return -1;
                break;
        }
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        rep(j,n) swap(A[j][i], A[j][bc]);
        bv = 1/A[i][i];
        repp(j,i+1,n) {
            double fac = A[j][i] * bv;
            b[j] -= fac * b[i];
            repp(k,i+1,m) A[j][k] -= fac*A[i][k];
        }
        rank++;
    }

    x.assign(m, 0);
    for (int i = rank; i--;) {
        b[i] /= A[i][i];
        x[col[i]] = b[i];
        rep(j,i) b[j] -= A[j][i] * b[i];
    }
    return rank; // (multiple solutions if rank < m)
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    while (cin >> n && n) {
        vector<vd> A(n, vd(n));
        rep(i,n) rep(j,n) cin >> A[i][j];
        vd b(n);
        rep(i,n) cin >> b[i];
        vd x(n);
        int rank = solveLinear(A,b,x);
        if (rank==-1) {
            cout << "inconsistent\n";
        }
        else if (rank<n) {
            cout << "multiple\n";
        }
        else {
            repe(v, x) {
                cout << fixed << setprecision(15) << v << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}
