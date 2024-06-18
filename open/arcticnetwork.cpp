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
		int s, p;
		cin >> s >> p;

		vector<pair<double, double>> outposts(p);
		rep(i, p) cin >> outposts[i].first >> outposts[i].second;

		vector<tuple<double, int, int>> edges;
		rep(i, p)
		{
			rep(j, p)
			{
				if (i == j) continue;
				edges.emplace_back(sqrt(pow(outposts[i].first - outposts[j].first, 2) + pow(outposts[i].second - outposts[j].second, 2)),
					i,j);
			}
		}
		sort(all(edges));

		double ans = 0;
		UF uf(p);
		int numcomps = p;
		repe(e, edges)
		{
			if (numcomps<=s)
			{
				ans = 0;
				break;
			}
			double d;
			int a, b;
			tie(d, a, b) = e;
			if (uf.find(a)!=uf.find(b))
			{
				uf.merge(a, b);
				numcomps--;
			}
			if (numcomps  <= s)
			{
				ans = d;
				break;
			}
		}

		cout << fixed << setprecision(2) << ans << "\n";
	}

	return 0;
}
