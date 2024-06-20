#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e6);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


pair<int, vi> hungarian(const vector<vi>& a) {
	if (a.empty()) return { 0, {} };
	int n = sz(a) + 1, m = sz(a[0]) + 1;
	vi u(n), v(m), p(m), ans(n - 1);
	repp(i, 1, n) {
		p[0] = i;
		int j0 = 0; // add "dummy" worker 0
		vi dist(m, int(1e14)), pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			int i0 = p[j0], j1, delta = int(1e14);
			repp(j, 1, m) if (!done[j]) {
				auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			repp(j, 0, m) {
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0) { // update alternating path
			int j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	repp(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
	return { -v[0], ans }; // min cost
}


signed main()
{
	fast();

	int n, m, k;
	cin >> m >> n >> k;
	bool swapped = 0;
	if (n < m) swap(n, m), swapped = 1;
	vvi cost(m, vi(n, 0));
	rep(_, k)
	{
		int i, j, p;
		cin >> i >> j >> p;
		i--; j--;
		if (!swapped) swap(i, j);
		cost[i][j] = -p;
	}
	pair<int, vi> res = hungarian(cost);
	vector<p2> ans;
	rep(i, sz(res.second))
	{
		p2 p = p2(i, res.second[i]);
		if (!swapped) swap(p.first, p.second);
		ans.emplace_back(p);
	}
	cout << -res.first << "\n";
	cout << sz(ans) << "\n";
	repe(e, ans) cout << e.first + 1 << " " << e.second + 1 << "\n";


	return 0;
}
