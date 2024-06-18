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

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		UF uf(n);

		vector<pair<double, double>> p(n);
		rep(i, n)cin >> p[i].first >> p[i].second;

		vector<tuple<double, int, int>> edges;
		rep(i, n)
		{
			rep(j, n)
			{
				if (i == j) continue;
				edges.emplace_back(sqrt(pow(p[i].first-p[j].first, 2) + pow(p[i].second-p[j].second,2)), i, j);
			}
		}
		sort(all(edges));

		double ans = 0;
		repe(e, edges)
		{
			double d;
			int a, b;
			tie(d, a, b) = e;
			if (uf.find(a)!=uf.find(b))
			{
				uf.merge(a, b);
				ans += d;
			}
		}

		cout << fixed << setprecision(15) << ans << "\n";
	}

	return 0;
}
