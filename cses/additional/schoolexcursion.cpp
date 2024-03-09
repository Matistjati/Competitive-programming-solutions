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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int compsz[int(1e5)];
int comp = 0;
int vis[int(1e5)];
void dfs(int u, vvi& adj)
{
	if (vis[u]) return;
	vis[u] = 1;
	compsz[comp]++;
	repe(e, adj[u]) dfs(e, adj);
}

signed main()
{
	fast();

	memset(compsz, 0, sizeof(compsz));
	memset(vis, 0, sizeof(vis));
	int n, m;
	cin >> n >> m;

	vvi adj(n);
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	rep(i, n)
	{
		if (vis[i]) continue;
		dfs(i, adj);
		comp++;
	}

	bitset<int(1e5 + 10)> bset;
	bset[0] = 1;
	rep(i, comp)
	{
		bset |= bset << compsz[i];
	}
	repp(i, 1, n + 1) cout << bset[i];

	return 0;
}
