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

	string a, b;
	while (cin >> a >> b)
	{
		map<string, int> nameid;
		vector<vector<p2>> adj;
		vector<string> name;
		auto add_name = [&](string x)
			{
				if (!nameid.count(x)) nameid[x] = sz(nameid), adj.push_back({}), name.push_back(x);
			};

		add_name(a);
		add_name(b);

		int g;
		cin >> g;
		cin.ignore(1, '\n');
		rep(i, g)
		{
			string line;
			getline(cin, line);
			vector<string> group;
			while (sz(line))
			{
				string token;
				while (sz(line)&&line.back()!=' ')
				{
					token += line.back();
					line.pop_back();
				}
				reverse(all(token));
				group.push_back(token);
				if (sz(line)) line.pop_back();
			}
			repe(m, group) add_name(m);

			string fakenodename = "AAAAAAAAAAAAAAAA" + to_string(i);
			add_name(fakenodename);
			int fakenode = nameid[fakenodename];

			repe(m, group)
			{
				adj[nameid[m]].emplace_back(fakenode, sz(group) - 1);
				adj[fakenode].emplace_back(nameid[m], 0);
			}
		}

		priority_queue<p2> pq;
		vi dist(sz(adj), inf);
		vi par(sz(adj), -2);
		dist[nameid[a]] = 0;
		pq.emplace(0, nameid[a]);
		while (sz(pq))
		{
			int d, u;
			tie(d, u) = pq.top();
			pq.pop();

			d = -d;
			if (d > dist[u]) continue;
			if (u == nameid[b]) break;

			repe(e, adj[u])
			{
				int nd = d + e.second;
				if (nd<dist[e.first])
				{
					par[e.first] = u;
					dist[e.first] = nd;
					pq.emplace(-nd, e.first);
				}
			}
		}

		

		if (dist[nameid[b]] == inf) cout << "impossible\n";
		else
		{
			int u = nameid[b];
			vector<string> ans;
			while (u!=-2)
			{
				ans.push_back(name[u]);
				u = par[u];
			}
			reverse(all(ans));


			cout << dist[nameid[b]]-1 << " ";
			repe(node, ans) if (node.find("AAAAAAAAAAAAAAAA")!=0) cout << node << " ";
			cout << "\n";
		}
	}

	return 0;
}
