#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

struct UF
{
	vi par;
	vi size;
	UF(int n) : par(n), size(n, 1)
	{
		rep(i, n) par[i] = i;
	}
	int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		par[b] = a;
		size[a] += size[b];
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m;
	cin >> n >> m;
	UF uf(n);
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		uf.merge(a, b);
	}
	int cc = 0;
	vi seen(n);
	rep(i, n)
	{
		int x = uf.find(i);
		if (!seen[x])
		{
			seen[x] = 1;
			cc++;
		}
	}
	ll ans = 1;
	const ll mod = ll(1e9 + 9);
	rep(i, m - n + cc)
	{
		ans = (ans * 2) % mod;
	}
	cout << ans << '\n';

	return 0;
}
