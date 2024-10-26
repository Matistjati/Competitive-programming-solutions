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


bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if (a != -1) A[a] = -1;
		repp(a, 0, sz(g)) if (A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		repp(a, 0, sz(g))
			res += dfs(a, 0, g, btoa, A, B);
	}
}

signed main()
{
	fast();

	int n, k;
	cin >> n >> k;

	vector<p2> interval;
	int a;
	cin >> a;
	interval.emplace_back(0, a-1);
	rep(i, k - 1)
	{
		cin >> a;
		interval.emplace_back(interval.back().second + 1, interval.back().second + 1 + a - 1);
	}

	set<int> uniques;
	vvi like(n, vi(k));
	rep(i, n)
	{
		rep(j, k) cin >> like[i][j], uniques.insert(like[i][j]);
	}
	vi unique(all(uniques));
	
	auto solution_exists = [&](int l, int r)
	{
		vvi adj(n);
		rep(i, n)
		{
			rep(j, k)
			{
				if (like[i][j]>=unique[l]&&like[i][j]<=unique[r])
				{
					repp(k,interval[j].first,interval[j].second+1) adj[i].push_back(k);
				}
			}
		}
		vi btoa(n,-1);
		return hopcroftKarp(adj, btoa) == n;
	};

	int ans = inf;
	int r = 0;
	rep(l, sz(unique))
	{
		while (r < sz(unique) && !solution_exists(l,r))
		{
			r++;
		}
		if (r<sz(unique)) ans = min(ans, unique[r] - unique[l]);
	}
	cout << ans;

	return 0;
}
