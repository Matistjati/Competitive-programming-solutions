#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

vi val;
vvi adj;
const ll maxv = 5000;

vi primes;
vvi factors;

vi ans(int u, int p)
{
	vi ret(maxv,inf);
	repp(i, 2, maxv) ret[i] = i;
	ret[val[u]] = 0;

	repe(e, adj[u]) if (e != p)
	{
		vi c = ans(e, u);

		vi minc(sz(primes), inf);
		rep(i, sz(primes))
		{
			int p = primes[i];
			for (int j = p; j < maxv; j+=p) minc[i] = min(minc[i], c[j]);
		}
		repp(i, 2, maxv)
		{
			ll cost = inf;
			repe(f, factors[i])
			{
				cost = min(cost, minc[f]);
			}
			ret[i] += cost;
		}
	}

	return ret;
}


int main()
{
	cin.tie(0)->sync_with_stdio(0);
	
	repp(i, 2, maxv)
	{
		bool isprime = 1;
		repp(j, 2, i) isprime &= i % j != 0;
		if (isprime) primes.push_back(i);
	}
	factors.resize(maxv);
	repp(i, 2, maxv)
	{
		set<int> factor;
		int v = i;
		repp(j, 2, i+1)
		{
			while (v%j==0)
			{
				factor.insert(j);
				v /= j;
			}
		}
		vi ff;
		repe(f, factor)
		{
			ff.push_back(lower_bound(all(primes), f) - begin(primes));
		}
		factors[i] = ff;
	}

	int n;
	cin >> n;
	val.resize(n);
	repe(v, val) cin >> v;
	adj.resize(n);
	rep(i, n - 1)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vi c = ans(0, 0);
	ll finalans = inf;
	repp(i, 2, maxv) finalans = min(finalans, c[i]);
	cout << finalans << '\n';

	return 0;
}
