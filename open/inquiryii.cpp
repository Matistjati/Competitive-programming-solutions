#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = 1e18;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

typedef vector<bitset<200>> vb;
struct Maxclique {
	double limit = 0.025, pk = 0;
	struct Vertex { int i, d = 0; };
	typedef vector<Vertex> vv;
	vb e;
	vv V;
	vector<vi> C;
	vi qmax, q, S, old;
	void init(vv& r) {
		for (auto& v : r) v.d = 0;
		for (auto& v : r) for (auto j : r) v.d += e[v.i][j.i];
		sort(all(r), [](auto a, auto b) { return a.d > b.d; });
		int mxD = r[0].d;
		repp(i, 0, sz(r)) r[i].d = min(i, mxD) + 1;
	}
	void expand(vv& R, int lev = 1) {
		S[lev] += S[lev - 1] - old[lev];
		old[lev] = S[lev - 1];
		while (sz(R)) {
			if (sz(q) + R.back().d <= sz(qmax)) return;
			q.push_back(R.back().i);
			vv T;
			for (auto v : R) if (e[R.back().i][v.i]) T.push_back({ v.i });
			if (sz(T)) {
				if (S[lev]++ / ++pk < limit) init(T);
				int j = 0, mxk = 1, mnk = max(sz(qmax) - sz(q) + 1, 1LL);
				C[1].clear(), C[2].clear();
				for (auto v : T) {
					int k = 1;
					auto f = [&](int i) { return e[v.i][i]; };
					while (any_of(all(C[k]), f)) k++;
					if (k > mxk) mxk = k, C[mxk + 1].clear();
					if (k < mnk) T[j++].i = v.i;
					C[k].push_back(v.i);
				}
				if (j > 0) T[j - 1].d = 0;
				repp(k, mnk, mxk + 1) for (int i : C[k])
					T[j].i = i, T[j++].d = k;
				expand(T, lev + 1);
			}
			else if (sz(q) > sz(qmax)) qmax = q;
			q.pop_back(), R.pop_back();
		}
	}
	vi maxClique() { init(V), expand(V); return qmax; }
	Maxclique(vb conn) : e(conn), C(sz(e) + 1), S(sz(C)), old(S) {
		repp(i, 0, sz(e)) V.push_back({ i });
	}
};

signed main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n,m;
	cin >> n >> m;
	vb adj(n);

	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		adj[a][b] = 1;
		adj[b][a] = 1;
	}

	rep(i, n) adj[i] = ~adj[i], adj[i][i] = 0;

	cout << sz(Maxclique(adj).maxClique()) << "\n";

	return 0;
}
