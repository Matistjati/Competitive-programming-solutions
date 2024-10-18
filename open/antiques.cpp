#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8;
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

// ILP. Maximize
bool is_integer(double x)
{
	return abs(x - floor(x)) < eps;
}

bool is_feasible(vd& x, vvd& A, vd& b, vi& integer_constraint)
{
	rep(i, sz(x))
	{
		if (integer_constraint[i] && !is_integer(x[i])) return false;
	}
	rep(i, sz(b))
	{
		double v = 0;
		rep(j, sz(x)) v += x[j] * A[i][j];
		if (v > b[i]) return false;
	}

	return true;
}

auto start = chrono::high_resolution_clock::now();
double global_lb = -inf;
vvd A;
vd b, c;
vi integer_constraint;
struct node
{
	double ub;
	vd x;
	int var_index;
	int smaller;
	bool pruned = 0;
	node(int var_index, int smaller) : smaller(smaller), var_index(var_index)
	{
		x.resize(sz(c));
		ub = LPSolver(A, b, c).solve(x);
		if (ub == -inf) pruned = 1;
		if (ub < global_lb)
		{
			pruned = 1;
		}

		auto check_sol = [&](vd& x)
		{
			if (!is_feasible(x, A, b, integer_constraint)) return false;
			double value = 0;
			rep(i, sz(x)) value += x[i] * c[i];
			global_lb = max(global_lb, value);
			return true;
		};

		// try to obtain lower bounds
		if (check_sol(x))
		{
			// if simplex gave us integers, no point in branching from this node
			pruned = 1;
		}
		else
		{
			// try to round for bounds
			vd rounded(x);
			rep(i, sz(rounded)) rounded[i] = floor(rounded[i]);
			check_sol(rounded);

			rounded = x;
			rep(i, sz(rounded)) rounded[i] = ceil(rounded[i]);
			check_sol(rounded);

			rounded = x;
			rep(i, sz(rounded)) rounded[i] = round(rounded[i]);
			check_sol(rounded);
		}
	}
	void branch(int d)
	{
		if (d > 40)
		{
			return;
		}
		if (ub < global_lb)
		{
			return;
		}
		if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count()>1)
		{
			return;
		}

		vector<node*> children;

		rep(v, sz(c))
		{
			if (integer_constraint[v] && !is_integer(x[v]))
			{
				vd new_integrality(sz(c));
				// test v <= floor(x[v])
				new_integrality[v] = 1;
				b.push_back(floor(x[v]));
				A.push_back(new_integrality);
				children.emplace_back(new node(v, 1LL));
				b.pop_back();
				A.pop_back();

				// test v >= ceil(x[v])
				new_integrality[v] = -1;
				b.push_back(-ceil(x[v]));
				A.push_back(new_integrality);
				children.emplace_back(new node(v, 0LL));
				b.pop_back();
				A.pop_back();
				break;
			}
		}
		// branch on largest children first
		sort(all(children), [](node* a, node* b)
			{
				return a->ub > b->ub;
			});

		repe(child, children)
		{
			if (child->pruned) continue;
			int idx = child->var_index;
			vd new_integrality(sz(c));
			new_integrality[idx] = child->smaller ? 1 : -1;
			b.push_back(child->smaller ? floor(x[idx]) : -ceil(x[idx]));
			A.push_back(new_integrality);
			child->branch(d + 1);
			b.pop_back();
			A.pop_back();
		}
	}
};

signed main()
{
	fast();

	int n, m, k;
	cin >> n >> m >> k;

	int ans = 0;

	c.resize(m);
	vector<p2> edges;
	rep(i, n)
	{
		int a, ac, b, bc;
		cin >> a >> ac >> b >> bc;
		a--; b--;
		if (ac<bc)
		{
			ans += bc;
			c[a] += -(ac - bc);
		}
		else
		{
			ans += ac;
			c[b] += -(bc - ac);
		}
		edges.emplace_back(a, b);

	}

	repe(e, edges)
	{
		vd row(m);
		row[e.first] = -1;
		row[e.second] = -1;
		A.push_back(row);
		b.push_back(-1);
	}

	rep(i, m)
	{
		vd var(m);
		var[i] = 1;
		A.push_back(var);
		b.push_back(1);
	}

	vd row(m, 1);
	A.push_back(row);
	b.push_back(k);
	integer_constraint.resize(m, 1);

	node* root = new node(-1, -1);
	root->branch(0);
	if (global_lb==-inf)
	{
		cout << -1;
	}
	else cout << int(round(ans-global_lb));

	return 0;
}
