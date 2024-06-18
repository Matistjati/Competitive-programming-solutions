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

	int n, k;
	cin >> n >> k;

	vector<tuple<int, int, int>> edges;
	vector<string> nodes(n);
	rep(i, n)cin >> nodes[i];
	rep(i, n)
	{
		rep(j, n)
		{
			if (i == j) continue;
			string& a = nodes[i];
			string& b = nodes[j];
			int c = 0;
			rep(l, k) c += a[l] != b[l];
			edges.emplace_back(c, i, j);
		}
	}
	sort(all(edges));
	UF uf(n);
	int ans = 0;
	vector<p2> ans_edges;
	repe(e, edges)
	{
		int c, a, b;
		tie(c, a, b) = e;
		if (uf.find(a)!=uf.find(b))
		{
			ans += c;
			ans_edges.emplace_back(a, b);
			uf.merge(a, b);
		}
	}

	cout << ans << "\n";
	repe(e, ans_edges) cout << e.first << " " << e.second << "\n";

	return 0;
}
