#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

struct UF
{
	vi size, par;
	UF(int n) : size(n, 1), par(n)
	{
		rep(i, n) par[i] = i;
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

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--)
	{
		ll n, m, s, n_panels;
		cin >> n >> m >> s >> n_panels;

		UF uf(n);
		vector<tuple<ll, ll, ll>> edges;
		rep(i, m)
		{
			ll a, b, c;
			cin >> a >> b >> c;
			edges.emplace_back(c, a, b);
		}

		sort(all(edges));

		ll ans = inf;
		if (n_panels >= n) ans = n * s;
		ll cost = 0;
		ll num_comps = n;
		for (auto [c, a, b] : edges)
		{
			if (uf.find(a)!=uf.find(b))
			{
				uf.merge(a, b);
				num_comps--;
				cost += c;
				if (n_panels >= num_comps) ans = min(ans, cost + s * max(0LL, num_comps));
			}
		}
		assert(ans != inf);
		cout << ans << '\n';
	}

	return 0;
}
