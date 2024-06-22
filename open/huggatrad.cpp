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

#define _LOCAL _DEBUG
#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int n;
const int maxn = int(2e5);
int dp[2][maxn];
int mincost(int u, int p, bool isfree, vvi& edges)
{
	int& v = dp[isfree][u];
	if (v != -1) return v;
	int ret = isfree ? 0 : 1;


	vector<p2> childdp;
	repe(e, edges[u])
	{
		if (e == p) continue;
		p2 child = { mincost(e, u, 0, edges), mincost(e, u, 1, edges) };
		childdp.push_back(child);
	}

	if (childdp.empty()) return ret;


	int k = sz(childdp);

	int totfirst = 0;
	rep(i, k) totfirst += childdp[i].first;


	vi childv;
	rep(i, k) childv.push_back(childdp[i].second - childdp[i].first);
	sort(all(childv));

	if (isfree) // we can only take one child
	{
		totfirst += childv[0];
	}
	else // take 2 children
	{
		rep(i, min(2LL, k)) totfirst += childv[i];
	}
	ret += totfirst;

	return v = ret;
}

signed main()
{
	fast();

	memset(dp, -1, sizeof(dp));
	cin >> n;
	vvi edges(n);
	rep(i, n - 1)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	cout << mincost(0, 0, 0, edges) << "\n";

	return 0;
}
