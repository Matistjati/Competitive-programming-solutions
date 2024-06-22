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

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct UF
{
	vi par;
	vi size;
	vi compval;

	UF(int n) : par(n), size(n, 1), compval(n)
	{
		rep(i, n) par[i] = i;
	}

	int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
	void merge(int a, int b, int andv)
	{
		a = find(a); b = find(b);
		if (size[a] < size[b]) swap(a, b);
		compval[a] |= andv;
		if (a == b) return;
		par[b] = a;
		size[a] += size[b];
	}
};

signed main()
{
	fast();

	int n, m, q;
	cin >> n >> m >> q;
	UF uf(n);
	rep(i, m)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		uf.merge(a, b, c);
	}

	rep(i, q)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		if (uf.find(a) == uf.find(b)) cout << __builtin_popcount(uf.compval[uf.find(a)]) << "\n";
		else cout << "-1\n";
	}

	return 0;
}
