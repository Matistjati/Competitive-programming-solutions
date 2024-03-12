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

p2 mst(int n, vector<tuple<char, int, int>> edgelist)
{
	int colorcnt = 0;
	int edgecnt = 0;
	UF uf(n);

	rep(i, sz(edgelist))
	{
		char c;
		int a, b;
		tie(c, a, b) = edgelist[i];
		if (uf.find(a) != uf.find(b))
		{
			if (c == 'B')colorcnt++;
			edgecnt++;
			uf.merge(a, b);
		}
	}
	return { colorcnt,edgecnt };
}


signed main()
{
	fast();

	int n, m, k;
	cin >> n >> m >> k;

	vector<tuple<char, int, int>> edgelist;
	rep(i, m)
	{
		char c;
		cin >> c;
		int a, b;
		cin >> a >> b;
		a--; b--;
		edgelist.emplace_back(c, a, b);
	}
	sort(all(edgelist));

	p2 blue = mst(n, edgelist);
	sort(edgelist.rbegin(), edgelist.rend());
	p2 red = mst(n, edgelist);

	if (k <= blue.first && k >= red.first && blue.second == n - 1)
	{
		cout << "1";
	}
	else cout << "0";

	return 0;
}
