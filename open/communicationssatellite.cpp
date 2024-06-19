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
		rep(i, n)par[i] = i;
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

	int n;
	cin >> n;
	vector<tuple<int, int, int>> dishes;
	rep(i, n)
	{
		int x, y, r;
		cin >> x >> y >> r;
		dishes.emplace_back(x, y, r);
	}
	vector<tuple<double, int, int>> edges;
	rep(i, n)
	{
		rep(j, n)
		{
			if (i == j) continue;
			int x1, y1, r1, x2, y2, r2;
			tie(x1, y1, r1) = dishes[i];
			tie(x2, y2, r2) = dishes[j];
			double dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
			edges.emplace_back(dist - r1 - r2, i, j);
		}
	}
	sort(all(edges));
	double ans = 0;
	UF uf(n);
	repe(e, edges)
	{
		double d;
		int i, j;
		tie(d, i, j) = e;
		if (uf.find(i)!=uf.find(j))
		{
			uf.merge(i, j);
			ans += d;
		}
	}
	cout << fixed << setprecision(15) << ans;

	return 0;
}
