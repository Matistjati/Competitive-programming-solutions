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
	int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
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

	int n, m;
	cin >> n >> m;

	typedef tuple<int, int, int> p3;
	vector<p3> edges;
	rep(i, m)
	{
		int a, b, c;
		cin >> a >> b >> c;
		edges.emplace_back(c, a, b);
	}

	sort(all(edges));

	int numcomps = n;
	int largestedge = 0;
	UF uf(n);
	repe(e, edges)
	{
		int a, b, c;
		tie(c, a, b) = e;
		if (uf.find(a)!=uf.find(b))
		{
			uf.merge(a, b);
			numcomps--;
			largestedge = max(largestedge, c);
		}
	}
	if (numcomps > 1) cout << "IMPOSSIBLE";
	else cout << largestedge;

	return 0;
}
