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

int best(int u, int p, vector<vector<p2>>& adj)
{
	int ret = 0;

	repe(e, adj[u])
	{
		if (e.first == p) continue;
		ret += min(e.second, best(e.first, u, adj));
	}

	if (sz(adj[u]) == 1 && u!=p) ret = adj[u][0].second;
	return ret;
}

signed main()
{
	fast();

	int n, c;
	while (cin >> n >> c)
	{
		c--;

		vector<vector<p2>> adj(n);
		rep(i, n - 1)
		{
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			adj[a].emplace_back(b, c);
			adj[b].emplace_back(a, c);
		}

		cout << best(c, c, adj) << "\n";
	}

	return 0;
}
