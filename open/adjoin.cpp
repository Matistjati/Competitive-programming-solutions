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

int f = -1;
int df = -1;
void furthest(int u, int p, int d, vi& vis, vvi& adj)
{
	vis[u] = 1;
	if (d > df)
	{
		f = u;
		df = d;
	}

	repe(e, adj[u]) if (e != p)furthest(e, u, d + 1, vis, adj);
}

signed main()
{
	fast();

	int n, m;
	cin >> n >> m;
	vvi adj(n);
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vi distances;
	vi vis(n);
	rep(i, n)
	{
		if (vis[i]) continue;
		df = -1;
		furthest(i, i, 0, vis, adj);
		df = -1;
		furthest(f, f, 0, vis, adj);
		distances.push_back(df);
	}
	sort(all(distances));
	if (sz(distances) == 1)
	{
		cout << distances[0];
	}
	else
	{
		int ans = 0;
		if (sz(distances) > 2) ans = ceildiv(distances[sz(distances) - 2], 2) + 2 + ceildiv(distances[sz(distances) - 3], 2);
		ans = max(ans, distances.back());
		cout << max(ans, ceildiv(distances.back(), 2) + 1 + ceildiv(distances[sz(distances) - 2], 2));
	}

	return 0;
}