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
		vi dist(m, INT_MAX), pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			int i0 = p[j0], j1, delta = INT_MAX;
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

	int n, m;
	cin >> n >> m;
	vector<p2> bottles(n);
	rep(i, n) cin >> bottles[i].first >> bottles[i].second;
	vector<p2> couriers(m);
	rep(i, m)cin >> couriers[i].first >> couriers[i].second;
	p2 goal;
	cin >> goal.first >> goal.second;

	int ans = 0;
	rep(i, n)
	{
		ans += abs(goal.first - bottles[i].first) + abs(goal.second - bottles[i].second);
	}
	vvi cost(n, vi(n - 1 + m));
	rep(i, n)
	{
		rep(j, m)
		{
			cost[i][j] = abs(couriers[j].first - bottles[i].first) + abs(couriers[j].second - bottles[i].second);
		}
		rep(j, n - 1) cost[i][j+m] = abs(goal.first - bottles[i].first) + abs(goal.second - bottles[i].second);
	}

	ans += hungarian(cost).first;

	cout << ans;

	return 0;
}
