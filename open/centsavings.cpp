#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

ll cost(int rem)
{
	if (rem >= 5) return 10 - rem;
	return -rem;
}

ll memo[2001][10][22];

ll best(int u, int rem, int divsleft, vi& costs)
{
	if (u==sz(costs))
	{
		return cost(rem);
	}

	ll& v = memo[u][rem][divsleft];
	if (v != -1) return v;

	ll ret = inf;

	ret = min(ret, costs[u] + best(u + 1, (rem + costs[u]) % 10, divsleft, costs));
	if (divsleft)
	{
		ret = min(ret, cost(rem) + costs[u] + best(u + 1, costs[u]%10, divsleft-1, costs));
	}

	return v = ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

	memset(memo, -1, sizeof(memo));
	int n, d;
	cin >> n >> d;

	vi costs(n);
	repe(v, costs) cin >> v;

	cout << best(0, 0, d, costs) << '\n';


    return 0;
}
