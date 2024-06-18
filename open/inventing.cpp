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

typedef tuple<int, int, int> p3;
signed main()
{
	fast();

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<p3> weights;
		rep(i, n-1)
		{
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			weights.emplace_back(c,a,b);
		}
		UF uf(n);
		sort(all(weights));

		int ans = 0;
		int compsz = 0;
		int s = 0;
		rep(i, n - 1)
		{
			int a, b, c;
			tie(c, a, b) = weights[i];
			ans += (c + 1) * uf.size[uf.find(a)]*uf.size[uf.find(b)]-1;
			uf.merge(a, b);
		}
		cout << ans << "\n";
	}

	return 0;
}
