#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

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
	int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b])swap(a, b);
		par[b] = a;
		size[a] += size[b];
	}
};

signed main()
{
	fast();

	int n, m;
	cin >> n >> m;

	UF uf(n);
	unordered_set<int> edges;
	while (m--)
	{
		char t;
		int a, b;
		cin >> t >> a >> b;
		p2 orig = p2(a, b);
		if (a > b) swap(a, b);
		if (t=='f')
		{
			edges.insert(a * int(1e6) + b);
			uf.merge(a, b);
		}
		else
		{
			if (edges.find(a*int(1e6)+b)!=edges.end())
			{
				cout << orig.first << " + " << orig.second << "\n";
			}
			else if (uf.find(a)==uf.find(b))
			{
				cout << orig.first << " - " << orig.second << "\n";
			}
			else
			{
				cout << orig.first << " ? " << orig.second << "\n";
			}
		}
	}

	return 0;
}
