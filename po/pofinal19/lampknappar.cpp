#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e9);//int(1e18);

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

int dist[510][510];
int rdist[510][510];

signed main()
{
	fast();

	int n;
	cin >> n;
	rep(i, n) rep(j, n) dist[i][j] = inf;
	rep(i, n) rep(j, n) rdist[i][j] = inf;
	rep(i, n) dist[i][i] = 0;
	rep(i, n) rdist[i][i] = 0;

	vvi adj(n);
	vvi radj(n);
	rep(i, n)
	{
		int k;
		cin >> k;
		rep(j, k)
		{
			int x;
			cin >> x;
			x--;
			adj[i].push_back(x);
			radj[x].push_back(i);
			dist[i][x] = 1;
			rdist[x][i] = 1;
		}
	}

	rep(k, n) rep(i, n) rep(j, n) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	rep(k, n) rep(i, n) rep(j, n) rdist[i][j] = min(rdist[i][j], rdist[i][k] + rdist[k][j]);

	priority_queue<tuple<int, int, int>> pq;
	pq.emplace(0, 0, 0);
	vvi dp(n, vi(n, inf));

	auto relax = [&](int d, int a, int b)
	{
		if (d < dp[a][b])
		{
			dp[a][b] = d;
			pq.emplace(-d, a, b);
		}
	};

	while (sz(pq))
	{
		int d, a, b;
		tie(d, a, b) = pq.top();
		pq.pop();

		d = -d;
		if (d > dp[a][b]) continue;

		if (a==n-1&&b==n-1)
		{
			cout << d;
			return 0;
		}


		if (a!=b)
		{
			relax(d + dist[a][b] - 1, b, a);
		}

		rep(j, n)
		{
			if (a == b && a==j) continue;
			relax(d + dist[a][j] + rdist[b][j] - 1, j, j);
		}
		repe(e, adj[a])
		{
			relax(d + 1, e, b);
		}
		repe(e, radj[b])
		{
			relax(d + 1, a, e);
		}
	}
	cout << "nej";

	return 0;
}
