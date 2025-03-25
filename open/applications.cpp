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
	int numcomps;
	vi par;
	vi size;
	UF(int n) : numcomps(n), par(n), size(n, 1)
	{
		rep(i, n) par[i] = i;
	}
	int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		numcomps--;
		par[b] = a;
		size[a] += size[b];
	}
	int getsz(int u) { return size[find(u)]; }
};

signed main()
{
	fast();

	int s, a;
	cin >> s >> a;
	UF uf(s);

	rep(i, a)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--; c--;
		if (uf.getsz(a)==uf.getsz(b)&&uf.getsz(b)==uf.getsz(c)&&uf.getsz(c)==uf.getsz(a))
		{
			uf.merge(a, b);
			uf.merge(a, c);
		}
#define trymerge(a,b,c) \
		if (uf.find(a)==uf.find(b)&&uf.getsz(a)>uf.getsz(c)) \
			uf.merge(a,c);
		
		trymerge(a, b, c);
		trymerge(b, c, a);
		trymerge(c, a, b);
		cout << uf.numcomps << "\n";
	}


	return 0;
}
