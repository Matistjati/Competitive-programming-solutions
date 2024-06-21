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

struct UF
{
	vi par;
	vi size;
	UF(int n) : par(n), size(n, 1)
	{
		rep(i, n) par[i] = i;
	}
	int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		par[b] = a;
		size[a] += size[b];
	}
};

signed main()
{
	fast();

	int n, m, p;
	cin >> n >> m >> p;
	
	vi unsafe(n);
	rep(i, p)
	{
		int u;
		cin >> u;
		u--;
		unsafe[u] = 1;
	}
	if (n == 2&&unsafe[0]&&unsafe[1])
	{
		int best = inf;
		if (m == 0)
		{
			cout << "impossible";
			return 0;
		}
		rep(i, m)
		{
			int _, __, c;
			cin >> _ >> __ >> c;
			best = min(best, c);
		}
		cout << best;
		return 0;
	}
	UF uf(n);
	vector<tuple<int, int, int>> edges;
	vector<tuple<int, int, int>> leafedges;
	rep(i, m)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		if (unsafe[a] && unsafe[b]) continue;
		if (unsafe[a] || unsafe[b]) leafedges.emplace_back(c, a, b);
		else edges.emplace_back(c, a, b);
	}
	sort(all(edges));
	sort(all(leafedges));
	int ans = 0;
	int num_components = n;
	repe(e, edges)
	{
		int c, a, b;
		tie(c, a, b) = e;
		assert(!unsafe[a] && !unsafe[b]);
		if (uf.find(a)!=uf.find(b))
		{
			uf.merge(a, b);
			num_components--;
			ans += c;
		}
	}
	vi deg(n);
	repe(e, leafedges)
	{
		int c, a, b;
		tie(c, a, b) = e;

		assert(unsafe[a] + unsafe[b] == 1);
		if (!unsafe[a]) swap(a, b);
		if (deg[a]) continue;

		if (uf.find(a)!=uf.find(b))
		{
			deg[a]++;
			uf.merge(a, b);
			num_components--;
			ans += c;
		}
	}
	if (num_components > 1) cout << "impossible";
	else cout << ans;

	return 0;
}
