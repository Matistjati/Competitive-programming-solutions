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



signed main()
{
	fast();

	int g, n, m;
	cin >> g >> n >> m;

	vvi dist(n, vi(n, inf));

	rep(i, m)
	{
		int a, b, t;
		cin >> a >> b >> t;
		a--; b--;
		dist[a][b] = min(dist[a][b], t);
		dist[b][a] = min(dist[b][a], t);
	}

	rep(i, n) dist[i][i] = 0;
	rep(k,n)
		rep(i,n)
			rep(j,n)
				dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);

	vector<priority_queue<p2>> venues(n);
	vi bestvenue(n, -int(1e9));
	auto insert = [&](int p, int t, int profit)
	{
		rep(i, n)
		{
			venues[i].emplace(-(t + dist[p][i]), profit);
		}
	};
	insert(0, 0, 0);

	vector<tuple<int, int, int, int>> gigs;
	rep(i, g)
	{
		int l, r, v, p;
		cin >> v >> l >> r >> p;
		v--;
		gigs.emplace_back(l, r, v, p);
	}
	sort(all(gigs));

	int ans = 0;
	rep(i, g)
	{
		int l, r, v, p;
		tie(l, r, v, p) = gigs[i];

		while (sz(venues[v]) && -venues[v].top().first<=l)
		{
			bestvenue[v] = max(bestvenue[v], venues[v].top().second);
			venues[v].pop();
		}

		ans = max(ans, bestvenue[v] + p);
		insert(v, r, bestvenue[v] + p);
	}
	cout << ans;

	return 0;
}
