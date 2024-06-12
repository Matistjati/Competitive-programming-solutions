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
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

struct state
{
	int a, b;
	int parb, sizea, gooda;
};

struct UF
{
	vector<state> history;
	vi par;
	vi size;
	vi good;
	UF(int n) : par(n), size(n, 1), good(n)
	{
		rep(i, n)par[i] = i;
	}
	int find(int x) { return x == par[x] ? x : find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		state c = { a,b,par[b],size[a],good[a] };

		history.push_back(c);
		par[b] = a;
		size[a] += size[b];
		good[a] |= good[b];
	}
	void undo()
	{
		state s = history.back();
		history.pop_back();
		par[s.b] = s.parb;
		size[s.a] = s.sizea;
		good[s.a] = s.gooda;
	}
};

int bestcost = inf;
vi initialdeg;
vvi cost;
int n;
vector<p2> conedges;
typedef tuple<int, int, int> p3;
vvi vis;
int version = 0;
void rec(int c, int edgeind, int mask, int compcnt, UF& uf)
{
	if (compcnt == 1)
	{
		version++;
		//cout << "YAS\n";
		priority_queue<p3> pq;
		pq.emplace(0, mask, 0);
		while (pq.size())
		{
			int pcost, mask, node;
			tie(pcost, mask, node) = pq.top();
			pq.pop();
			if (vis[node][mask] == version) continue;
			vis[node][mask] = version;

			if (mask == 0)
			{
				bestcost = min(bestcost, c - pcost);
				break;
			}

			if (node + 1 < n && (mask & (1 << node)) == 0) pq.emplace(pcost, mask, node + 1);
			repp(i, node + 1, n)
			{
				if (cost[node][i] == inf) continue;
				int newmask = mask;
				newmask ^= 1 << i;
				newmask ^= 1 << node;
				pq.emplace(pcost - cost[node][i], newmask, node);
			}
		}
		return;
	}
	if (edgeind == sz(conedges)) return;

	rec(c, edgeind + 1, mask, compcnt, uf);


	int a, b;
	tie(a, b) = conedges[edgeind];
	if (uf.find(a) != uf.find(b) &&
		c + cost[a][b] < bestcost)
	{
		int merged = uf.good[uf.find(a)] > 0 && uf.good[uf.find(b)] > 0;
		uf.merge(a, b);
		int newmask = mask;
		newmask ^= (1 << a);
		newmask ^= (1 << b);
		rec(c + cost[a][b], edgeind + 1, newmask, compcnt - merged, uf);
		uf.undo();
	}

}

typedef tuple<int, int, int> p3;
signed main()
{
	fast();


	int m;
	cin >> n >> m;
	vis.resize(n, vi(1 << n));
	int t = 0;
	vi deg(n);
	vector<p3> edges;
	cost.resize(n, vi(n, inf));
	initialdeg.resize(n);
	UF uf(n);
	int compcnt = n;
	rep(i, m)
	{
		int a, b, c;
		cin >> a >> b >> c;
		t += c;
		a--; b--;
		deg[a]++;
		deg[b]++;
		if (uf.find(a) != uf.find(b))
		{
			compcnt--;
			uf.merge(a, b);
		}
		initialdeg[a]++;
		initialdeg[b]++;
		cost[a][b] = min(cost[a][b], c);
		cost[b][a] = min(cost[a][b], c);
		edges.emplace_back(a, b, c);
	}
	repp(i, 1, n) if (initialdeg[i] == 0) compcnt--;
	initialdeg[0] = 1;
	rep(i, n) if (initialdeg[i]) uf.good[uf.find(i)] = 1;
	int f;
	cin >> f;
	set<p2> conedgeset;
	vi w;
	rep(i, f)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		cost[a][b] = min(cost[a][b], c);
		cost[b][a] = min(cost[a][b], c);
		if (a < b) swap(a, b);
		w.push_back(c);
		conedgeset.insert(p2(a, b));
	}

	conedges = vector<p2>(all(conedgeset));
	int mask = 0;
	rep(i, n) if (deg[i] % 2) mask += (1 << i);

	rec(t, 0, mask, compcnt, uf);
	cout << bestcost;

	return 0;
}
