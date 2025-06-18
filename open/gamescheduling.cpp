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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }


vi edgeColoring(int N, vector<p2> eds) {
	vi cc(N + 1), ret(sz(eds)), fan(N), free(N), loc;
	for (p2 e : eds) ++cc[e.first], ++cc[e.second];
	int u, v, ncols = *max_element(all(cc)) + 1;
	vector<vi> adj(N, vi(ncols, -1));
	for (p2 e : eds) {
		tie(u, v) = e;
		fan[0] = v;
		loc.assign(ncols, 0);
		int at = u, end = u, d, c = free[u], ind = 0, i = 0;
		while (d = free[v], !loc[d] && (v = adj[u][d]) != -1)
			loc[d] = ++ind, cc[ind] = d, fan[ind] = v;
		cc[loc[d]] = c;
		for (int cd = d; at != -1; cd ^= c ^ d, at = adj[at][cd])
			swap(adj[at][cd], adj[end = at][cd ^ c ^ d]);
		while (adj[fan[i]][d] != -1) {
			int left = fan[i], right = fan[++i], e = cc[i];
			adj[u][e] = left;
			adj[left][e] = u;
			adj[right][e] = -1;
			free[right] = e;
		}
		adj[u][d] = fan[i];
		adj[fan[i]][d] = u;
		for (int y : {fan[0], u, end})
			for (int& z = free[y] = 0; adj[y][z] != -1; z++);
	}
	repp(i, 0, sz(eds))
		for (tie(u, v) = eds[i]; adj[u][ret[i]] != v;) ++ret[i];
	return ret;
}

signed main()
{
    fast();

	int n, m;
	cin >> n >> m;
	vector<p2> edges;
	rep(team, m)
	{
		repp(o, team+1, m)
		{
			rep(i, n)
			{
				rep(j, n)
				{
					int u = team * n + i;
					int v = o * n + j;
					assert(u != v);
					edges.emplace_back(u, v);
				}
			}
		}
	}

	vi res = edgeColoring(n*m, edges);

	auto format = [n,m](int u)
		{
			return string(1,((u / n) + 'A')) + to_string(u % n + 1);
		};
	map<int, vi> rounds;
	rep(i, sz(res)) rounds[res[i]].push_back(i);
	repe(r,rounds)
	{
		repe(e, r.second)
		{
			cout << format(edges[e].first) << "-" << format(edges[e].second) << " ";
		}
		cout << '\n';
	}


    return 0;
}
