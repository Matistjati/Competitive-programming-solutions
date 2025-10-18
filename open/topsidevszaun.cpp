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


int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vi strengths(n);
	repe(v, strengths) cin >> v;

	mt19937 rng(42);
	shuffle(all(strengths), rng);

	int window_size = 30;

	vvi dp(2 * window_size, vi(2 * window_size * 300, -inf));
	vvi nextdp(2*window_size, vi(2*window_size * 300, -inf));
	dp[window_size][window_size*300] = 0;
	nextdp[window_size][window_size * 300] = 0;
	// dp[size a - size b][skill a - skill b]
	repe(s, strengths)
	{
		// add to team A
		rep(sd, sz(dp)-1)
		{
			rep(skilldiff, sz(dp[0]))
			{
				if (skilldiff + s >= sz(dp[0])) continue;
				nextdp[sd + 1][skilldiff + s] = max(nextdp[sd + 1][skilldiff + s], 1 + dp[sd][skilldiff]);
			}
		}
		// add to team b
		repp(sd, 1, sz(dp))
		{
			rep(skilldiff, sz(dp[0]))
			{
				if (skilldiff - s < 0) continue;
				nextdp[sd - 1][skilldiff - s] = max(nextdp[sd - 1][skilldiff - s], dp[sd][skilldiff]);
			}
		}
		dp = nextdp;
	}
	cout << dp[window_size][window_size * 300] << '\n';

	return 0;
}
