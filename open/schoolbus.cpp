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

ll comp(int i, int c, vi & dp, vector<p2>& pos, vi & w)
{
	if (i==sz(pos))
	{
		return 0;
	}
	ll& v = dp[i];
	if (v != -1) return v;

	ll ret = inf;
	int tot_w = 0;
	ll tot_dist = 0;
	p2 p = { 0,0 };
	repp(j, i, sz(pos))
	{
		tot_w += w[j];
		if (tot_w > c) break;
		tot_dist += abs(pos[j].first - p.first) + abs(pos[j].second - p.second);
		p = pos[j];

		ret = min(ret, tot_dist + pos[j].first + pos[j].second + comp(j + 1, c, dp, pos, w));
	}
	return v=ret;
}


int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	// 500 * f^2
	while (t--)
	{
		ll c, n;
		cin >> c >> n;
		vector<p2> pos(n);
		vi w(n);
		rep(i, n)
		{
			cin >> pos[i].first >> pos[i].second >> w[i];
		}
		vi dp(n, -1);
		cout << comp(0, c, dp, pos, w) << '\n';

	}

	return 0;
}
