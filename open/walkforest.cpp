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

void topsort(int u, vi& vis, vi& order, vvi& adj)
{
	if (vis[u]) return;
	vis[u] = 1;

	repe(e, adj[u]) topsort(e, vis, order, adj);
	order.push_back(u);
}

signed main()
{
	fast();

	typedef tuple<int, int, int> p3;

	int n, m;
	while (cin >> n >> m && n)
	{
		vector<vector<p2>> adj(n);
		vector<p3> edges;
		rep(i, m)
		{
			int a, b, d;
			cin >> a >> b >> d;
			a--; b--;
			edges.emplace_back(a, b, d);
			adj[a].emplace_back(b, d);
			adj[b].emplace_back(a, d);
		}

		priority_queue<p2> pq;
		pq.emplace(0, 1);

		vi dis(n, inf);
		while (sz(pq))
		{
			int d, u;
			tie(d, u) = pq.top();
			pq.pop();

			if (dis[u] != inf) continue;
			dis[u] = -d;

			repe(e, adj[u])
			{
				pq.emplace(d - e.second, e.first);
			}
		}

		vvi newadj(n);
		repe(e, edges)
		{
			int a, b, d;
			tie(a, b, d) = e;
			if (dis[a] < dis[b])
			{
				newadj[b].push_back(a);
			}
			if (dis[b] < dis[a])
			{
				newadj[a].push_back(b);
			}
		}

		vi vis(n);
		vi order;
		rep(i, n)
		{
			topsort(i, vis, order, newadj);
		}
		reverse(all(order));
		vi dp(n);
		dp[0] = 1;
		repe(u, order)
		{
			repe(e, newadj[u])
			{
				dp[e] += dp[u];
			}
		}
		cout << dp[1] << "\n";
	}

	return 0;
}