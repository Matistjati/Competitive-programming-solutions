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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

vector<string> split(string s, string d) { size_t k = 0, n, e = d.length(); string t; vector<string> r; while ((n = s.find(d, k)) != string::npos) { t = s.substr(k, n - k); k = n + e; r.push_back(t); } r.push_back(s.substr(k)); return r; }

vector<bitset<5000>> adj;


vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ? val[e] : dfs(e, g, f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	repp(i, 0, n) if (comp[i] < 0) dfs(i, g, f);
}

signed main()
{
    fast();

    int n;
    cin >> n;
	vvi edges(n);
	adj.resize(n);
	
	repp(i, 1, n)
	{
		string row;
		cin >> row;
		rep(j, i)
		{
			if (row[j] == '1')
			{
				edges[i].push_back(j);
				adj[i][j] = 1;
			}
			else edges[j].push_back(i), adj[j][i]=1;
		}
	}

	vvi comps;
	scc(edges, [&](vi& v)
		{
			comps.push_back(v);
		});
	reverse(all(comps));

	int ans = 0;
	vi indeg(n);
	vi taken(n);
	
	repe(c, comps)
	{
		rep(i, sz(c))
		{
			repp(j, i+1, sz(c))
			{
				if (adj[c[i]][c[j]])
				{
					indeg[c[j]]++;
				}
				else indeg[c[i]]++;
			}
		}
		int cost = 0;
		int m = 0;
		sort(all(c), [&](int a, int b)
			{
				return indeg[a] < indeg[b];
			});
		int j = 0;
		repe(u, c)
		{
			cost += indeg[u];
			
			ans = max(ans, cost - j * (j + 1) / 2);
			j++;
		}
	}
	cout << ans;


    return 0;
}
