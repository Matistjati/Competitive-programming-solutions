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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define __builtin_clz __lzcnt
#define assert(x) if (!(x)) __debugbreak()
#endif

vi is_bridge;
vi allowed_bridge;
vi vis_e;
vector<vector<p2>> edges;
vi up;
vi vis;
vi depth;

void dfs(int u)
{
	repe(edg, edges[u])
	{
		int e, e_ind;
		tie(e, e_ind) = edg;
		if (vis[e]) // up edge
		{
			if (vis_e[e_ind]) continue;
			vis_e[e_ind] = 1;
			assert(depth[e] <= depth[u]);
			up[u] = min(up[u], depth[e]);
		}
		else
		{
			vis_e[e_ind] = 1;
			vis[e] = 1;
			depth[e] = depth[u] + 1;
			dfs(e);
			if (up[e]>=depth[e])
			{
				is_bridge[e_ind] = 1;
			}
			up[u] = min(up[u], up[e]);
		}
	}
}

bool dfs2(int a, int b)
{
	if (a == b) return 1;
	if (vis[a]) return 0;
	vis[a] = 1;

	repe(e, edges[a])
	{
		if (dfs2(e.first,b))
		{
			if (is_bridge[e.second]) allowed_bridge[e.second] = 1;
			return 1;
		}
	}

	return 0;
}

void dfs3(int a)
{
	if (vis[a]) return;
	vis[a] = 1;

	repe(e, edges[a])
	{
		if (is_bridge[e.second] && !allowed_bridge[e.second]) continue;
		dfs3(e.first);
	}
}

signed main()
{
	fast();

	int n, m, a, b;
	cin >> n >> m >> a >> b;
	depth.resize(n, -inf);
	depth[0] = 0;
	up.resize(n, inf);
	vis.resize(n);
	edges.resize(n);
	is_bridge.resize(m);
	allowed_bridge.resize(m);
	vis_e.resize(m);
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		edges[a].emplace_back(b,i);
		edges[b].emplace_back(a,i);
	}
	vis[a] = 1;
	dfs(a);
	rep(i, n) vis[i] = 0;
	dfs2(a, b);
	rep(i, n) vis[i] = 0;
	dfs3(a);

	int ans = 0;
	rep(i, n) ans += vis[i] == 0;
	cout << ans << "\n";
	rep(i, n) if (!vis[i]) cout << i << "\n";

	return 0;
}
