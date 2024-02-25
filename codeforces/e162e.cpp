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

int ans = 0;
map<int, int> dfs(int u, int p, vi& color, vvi& edges)
{
	map<int, int> ret;

	repe(e, edges[u])
	{
		if (e == p) continue;
		map<int, int> other = dfs(e, u, color, edges);
		if (other.size() > ret.size())swap(other, ret);

		repe(v, other)
		{
			if (v.first != color[u] && ret[v.first] > 0) ans += ret[v.first] * v.second;
			ret[v.first] += v.second;
		}
	}

	ans += ret[color[u]];

	ret[color[u]] = 1;
	return ret;
	//map<int, int> cp(ret);
	//return cp;
}

void solve()
{
	int n;
	cin >> n;
	vi color(n);
	rep(i, n) cin >> color[i];
	vvi edges(n);
	rep(i, n - 1)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	ans = 0;
	dfs(0, 0, color, edges);
	cout << ans << "\n";

}

signed main()
{
	fast();


	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}

	return 0;
}
