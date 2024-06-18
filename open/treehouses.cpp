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

typedef pair<double, double> pd;
typedef tuple<double, int, int> p3;
double sqr(double x) { return x * x; }
double dist(pd a, pd b)
{
	return sqrt(sqr(a.first-b.first)+sqr(a.second-b.second));
}
signed main()
{
	fast();

	int n, e, p;
	cin >> n >> e >> p;
	UF uf(n);
	rep(i, e - 1)
	{
		uf.merge(i, i + 1);
	}
	vector<pd> positions(n);
	rep(i, n)
	{
		cin >> positions[i].first >> positions[i].second;
	}
	rep(i, p)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		uf.merge(a, b);
	}
	vector<p3> edges;
	rep(i, n)
	{
		rep(j, n)
		{
			if (i == j) continue;
			edges.emplace_back(dist(positions[i], positions[j]), i, j);
		}
	}
	sort(all(edges));
	double ans = 0;
	repe(e, edges)
	{
		double d; int a, b;
		tie(d, a, b) = e;
		if (uf.find(a)!=uf.find(b))
		{
			uf.merge(a, b);
			ans += d;
		}
	}

	cout << fixed << setprecision(15) << ans;

	return 0;
}
