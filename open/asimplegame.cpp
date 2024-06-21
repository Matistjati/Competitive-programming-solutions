#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf2 = 100000000000;
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
			if (!simplex(2) || D[m + 1][n + 1] < -eps) return -inf2;
			repp(i, 0, m) if (B[i] == -1) {
				int s = 0;
				repp(j, 1, n + 1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		repp(i, 0, m) if (B[i] < n) x[B[i]] = D[i][n + 1];
		return ok ? D[m][n + 1] : inf2;
	}
};

signed main()
{
    fast();

	int r, c, _;
	cin >> r >> c >> _;
	vvd mat(r,vd(c));
	
	rep(i, r)
	{
		rep(j, c)
		{
			cin >> mat[i][j];
		}
	}
	
	auto solvebrute = [&]()
	{
		rep(i, int(1e5) + 1)
		{
			int b = int(1e5) - i;

		}
	};

	int cc = c;
	auto feasible = [&](double mid, bool outputans)
	{
		vvd a;
		vd c(r, 1);
		vd b;
		rep(i, cc)
		{
			vd row(r);
			rep(j, r)
			{
				row[j] = -mat[j][i];
			}
			a.push_back(row);
			b.push_back(-mid);
		}
		rep(i, r)
		{
			vd row2(r);
			row2[i] = -1;
			a.push_back(row2);
			b.push_back(0);
		}
		vd finalrow(r, 1);
		a.push_back(finalrow);
		b.push_back(int(1e5));
		LPSolver lp(a,b,c);
		vd x(r);
		double v = lp.solve(x);
		if (outputans)
		{
			rep(i, r) x[i] = round(x[i]);
			
			vi ans;
			rep(i, r)
			{
				rep(j, int(x[i]))
				{
					ans.push_back(i + 1);
				}
			}
			mt19937 rng(5);
			int ss = 100000;
			while (ans.size()<ss)
			{
				ans.push_back(rand() % r + 1);
			}
			while (ans.size() > ss) ans.pop_back();
			shuffle(all(ans), rng);
			
			assert(mid > _);
			assert(ans.size() == ss);
			repe(v, ans) cout << v << " ";
			exit(0);
		}
		return abs(v - 1e5) < 1e-5;
	};

	double lo = -1e9;
	double hi = 1e9;
	rep(i, 200)
	{
		double mid = (lo + hi) / 2;

		if (feasible(mid, false))
		{
			lo = mid;
		}
		else hi = mid;
	}

	feasible(lo, true);

    return 0;
}
