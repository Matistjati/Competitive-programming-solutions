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

struct edge
{
	int a, b, w, ind;
	bool operator<(edge& other)
	{
		if (w != other.w) return w < other.w;
		return ind < other.ind;
	}
	bool operator==(const edge& other)
	{
		return a == other.a && b == other.b && w == other.w && ind == other.ind;
	}
};

void dfs(int u, int p, vi& vis, vvi& adj)
{
	vis[u] = 1;
	repe(e, adj[u]) if (e != p) dfs(e, u, vis, adj);
}

struct UF
{
	vi par;
	vi size;
	UF(int n) : par(n), size(n, 1)
	{
		rep(i, n)par[i] = i;
	}
	int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a), b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		par[b] = a;
		size[a] += size[b];
	}
};

signed main()
{
	fast();

	int n, m;
	cin >> n >> m;
	vector<edge> edgelist;
	vector<edge> mst;
	vvi adj(n);
	rep(i, m)
	{
		int a, b, w;
		cin >> a >> b >> w;
		a--; b--;
		edgelist.push_back(edge({ a,b,w, i }));
		if (i < n - 1)
		{
			mst.push_back(edge({ a,b,w, i }));
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}
	sort(mst.rbegin(), mst.rend());
	sort(all(edgelist));
	UF uf(n);
	vector<edge> target;
	repe(e, edgelist)
	{
		if (uf.find(e.a) != uf.find(e.b))
		{
			auto it = find(all(mst), e);
			if (it != mst.end()) mst.erase(it);
			else target.push_back(e);

			uf.merge(e.a, e.b);
		}
	}

	auto erasee = [&](edge& e)
	{
		adj[e.a].erase(find(all(adj[e.a]), e.b));
		adj[e.b].erase(find(all(adj[e.b]), e.a));
	};

	auto inserte = [&](edge& e)
	{
		adj[e.a].push_back(e.b);
		adj[e.b].push_back(e.a);
	};

	vector<p2> ans;
	rep(i, sz(mst))
	{
		vi marked(n);
		dfs(mst[i].a, mst[i].b, marked, adj);

		int u = -1;
		rep(j, sz(target))
		{
			edge e = target[j];
			if (marked[e.a] != marked[e.b] && e.ind != mst[i].ind)
			{
				u = j;
				break;
			}
		}

		if (u != -1)
		{
			ans.emplace_back(mst[i].ind, target[u].ind);
			erasee(mst[i]);
			inserte(target[u]);
			target.erase(target.begin() + u);
		}
	}

	cout << ans.size() << "\n";
	repe(v, ans) cout << v.first + 1 << " " << v.second + 1 << "\n";
	return 0;
}
