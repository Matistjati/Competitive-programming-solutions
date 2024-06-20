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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Edmonds
{
	vvi flow;
	vvi capacity;
	vi par;
	int n;
	int tot_flow = 0;

	void addEdge(int a, int b, int c)
	{
		capacity[a][b] = c;
	}

	Edmonds(int n) : n(n), flow(n, vi(n)), capacity(n, vi(n)), par(n) {}

	int bfs(int s, int t)
	{
		rep(i, n) par[i] = -1;
		par[s] = -2;
		queue<p2> q;
		q.emplace(s, inf);

		while (q.size())
		{
			int u, f;
			tie(u, f) = q.front(); q.pop();

			rep(e, n)
			{
				if (par[e] == -1 && flow[u][e] < capacity[u][e])
				{
					par[e] = u;
					int newflow = min(f, capacity[u][e] - flow[u][e]);

					if (e == t) return newflow;
					q.emplace(e, newflow);
				}
			}
		}

		return 0;
	}

	int augment(int s, int t) // find one augmenting path
	{
		int f = 0;
		if (f = bfs(s, t))
		{
			tot_flow += f;
			for (int cur = t; cur != s; cur = par[cur])
			{
				int p = par[cur];
				flow[p][cur] += f;
				flow[cur][p] -= f;
			}

			return 1;
		}
		return 0;
	}

	int maxflow(int s, int t)
	{
		while(augment(s,t)) {}
		return tot_flow;
	}
};

signed main()
{
	fast();

	auto get_flow = [](vi& teamsolves, vi& problems)
	{
		int numnodes = sz(teamsolves) + sz(problems) + 2;
		Edmonds flow(numnodes);
		rep(i, sz(teamsolves))
		{
			flow.addEdge(numnodes - 2, i, teamsolves[i]);
		}
		rep(i, sz(problems))
		{
			flow.addEdge(sz(teamsolves) + i, numnodes - 1, problems[i]);
		}
		int ind = sz(teamsolves) * sz(problems);
		rep(i, sz(teamsolves))
		{
			rep(j, sz(problems))
			{
				flow.addEdge(i, sz(teamsolves) + j, 1);
			}
		}
		return flow;
	};

	int t, p;
	while (cin >> t >> p && t != 0)
	{
		vi teamsolves(t);
		rep(i, t) cin >> teamsolves[i];
		vi problems(p);
		rep(i, p) cin >> problems[i];

		if (accumulate(all(teamsolves), 0LL) != accumulate(all(problems), 0LL))
		{
			cout << "Impossible\n\n";
			continue;
		}

		int numnodes = sz(teamsolves) + sz(problems) + 2;
		Edmonds flow = get_flow(teamsolves, problems);
		int res = flow.maxflow(numnodes - 2, numnodes - 1);
		if (res != accumulate(all(teamsolves), 0LL))
		{
			cout << "Impossible\n\n";
			continue;
		}

		vvi ans(sz(teamsolves), vi(sz(problems)));
		rep(i, sz(teamsolves))
		{
			rep(j, sz(problems))
			{
				int k = sz(teamsolves) + j;
				if (flow.flow[i][k]>0) // if we use positive flow, try to change
				{
					flow.capacity[i][k] = 0;
					flow.flow[numnodes - 2][i]--;
					flow.flow[i][numnodes-2]++;
					flow.flow[i][k]--;
					flow.flow[k][i]++;
					flow.flow[k][numnodes - 1]--;
					flow.flow[numnodes-1][k]++;
					if (flow.augment(numnodes-2,numnodes-1)) // YAY! lexicographically smaller
					{

					}
					else
					{
						ans[i][j] = 1;
						flow.capacity[i][k] = 1;
						flow.flow[numnodes - 2][i]++;
						flow.flow[i][numnodes - 2]--;
						flow.flow[i][k]++;
						flow.flow[k][i]--;
						flow.flow[k][numnodes - 1]++;
						flow.flow[numnodes - 1][k]--;
					}
				}
				else
				{
					flow.capacity[i][k] = 0;
				}
			}
		}

		rep(i, sz(teamsolves))
		{
			rep(j, sz(problems))
			{
				cout << (ans[i][j] ? "Y" : "N");
			}
			cout << "\n";
		}
		cout << "\n";
	}

	return 0;
}
