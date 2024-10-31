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

	int n, m;
	cin >> n >> m;
	vi cost(n);
	rep(i, n) cin >> cost[i];

	vector<vector<p2>> adj(n);
	rep(i, m)
	{
		int u, v, d;
		cin >> u >> v >> d;
		adj[u].emplace_back(v, d);
		adj[v].emplace_back(u, d);
	}

	

	int q;
	cin >> q;
	
	int dist[101][1000];
	while (q--)
	{
		int s, e, c;
		cin >> c >> s >> e;
		rep(i, c+1) rep(j, n) dist[i][j] = inf;
		priority_queue<tuple<int,int,int>> pq;
		pq.emplace(0, 0, s);
		dist[0][s] = 0;
		int ans = inf;
		while (sz(pq))
		{
			int d, f, u;
			tie(d, f, u) = pq.top();
			pq.pop();

			d = -d;
			
			if (d > dist[f][u]) continue;


			if (u==e)
			{
				ans = d;
				break;
			}

			repp(new_fuel, f + 1, c + 1)
			{
				int new_d = d + (new_fuel - f) * cost[u];
				if (new_d < dist[new_fuel][u])
				{
					dist[new_fuel][u] = new_d;
					pq.emplace(-new_d, new_fuel, u);
				}
				
			}

			repe(e, adj[u])
			{
				int new_f = f - e.second;
				if (new_f < 0) continue;
				if (d<dist[new_f][e.first])
				{
					dist[new_f][e.first] = d;
					pq.emplace(-d, new_f, e.first);
				}
			}
		}
		if (ans != inf) cout << ans << "\n";
		else cout << "impossible\n";
	}

	return 0;
}
