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

bool dfs(int u, vi& vis, vi& match, vvi& edges)
{
	if (match[u] == -1) return 1;
	if (vis[u]) return 0;
	vis[u] = 1;
	int v = match[u];
	// try to match v to some other node on right
	repe(e, edges[v])
	{
		if (dfs(e, vis, match, edges))
		{
			match[e] = v;
			return 1;
		}
	}
	return 0;
}

signed main()
{
	fast();

	int a, b, m;
	cin >> a >> b >> m;

	vvi edges(a);
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		edges[a].push_back(b);
	}

	vi match(b, -1);
	rep(i, a)
	{
		vi vis(a);
		repe(e, edges[i])
		{
			if (dfs(e, vis, match, edges))
			{
				match[e] = i;
				break;
			}
		}
	}
	int ans = 0;
	rep(i, b) if (match[i] != -1) ans++;
	cout << ans << "\n";
	rep(i, b)
	{
		if (match[i] != -1) cout << match[i] + 1 << " " << i + 1 << "\n";
	}

	return 0;
}
