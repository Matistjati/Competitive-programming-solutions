#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)


typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = numeric_limits<double>::infinity();
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

struct LPSolver {
	int m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(sz(b)), n(sz(c)), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
		repp(i, 0, m) repp(j, 0, n) D[i][j] = A[i][j];
		repp(i, 0, m) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
		repp(j, 0, n) { N[j] = j; D[m][j] = -c[j]; }
		N[n] = -1; D[m + 1][n] = 1;
	}

	void pivot(int r, int s) {
		T* a = D[r].data(), inv = 1 / a[s];
		repp(i, 0, m + 2) if (i != r && abs(D[i][s]) > eps) {
			T* b = D[i].data(), inv2 = b[s] * inv;
			repp(j, 0, n + 2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		repp(j, 0, n + 2) if (j != s) D[r][j] *= inv;
		repp(i, 0, m + 2) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = m + phase - 1;
		for (;;) {
			int s = -1;
			repp(j, 0, n + 1) if (N[j] != -phase) ltj(D[x]);
			if (D[x][s] >= -eps) return true;
			int r = -1;
			repp(i, 0, m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || MP(D[i][n + 1] / D[i][s], B[i])
					< MP(D[r][n + 1] / D[r][s], B[r])) r = i;
			}
			if (r == -1) return false;
			pivot(r, s);
		}
	}

	T solve(vd& x) {
		int r = 0;
		repp(i, 1, m) if (D[i][n + 1] < D[r][n + 1]) r = i;
		if (D[r][n + 1] < -eps) {
			pivot(r, n);
			if (!simplex(2) || D[m + 1][n + 1] < -eps) return -inf;
			repp(i, 0, m) if (B[i] == -1) {
				int s = 0;
				repp(j, 1, n + 1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		repp(i, 0, m) if (B[i] < n) x[B[i]] = D[i][n + 1];
		return ok ? D[m][n + 1] : inf;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int m, n;
	cin >> m >> n;

	vd objective(n);
	vd amount(m);
	repe(v, amount) cin >> v;
	vvd A(m, vd(n));
	rep(i, n)
	{
		rep(j, m) cin >> A[j][i], A[j][i]/=100;
		cin >> objective[i];
	}
	vd x(n);
	cout << fixed << setprecision(15) << LPSolver(A, amount, objective).solve(x);

	return 0;
}
