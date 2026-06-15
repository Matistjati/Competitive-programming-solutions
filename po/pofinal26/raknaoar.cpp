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

	int n, q;
	cin >> n >> q;
	vi ans(q);

	vector<p2> islands;
	islands.reserve(3e5 + 10);
	rep(i, n)
	{
		int k;
		cin >> k;
		rep(j, k)
		{
			int x;
			cin >> x;
			islands.emplace_back(x, i);
		}
	}
	sort(all(islands));
	reverse(all(islands));

	vi cnt(n);
	vector<p2> queries(q);

	rep(i, q)
	{
		int x;
		cin >> x;
		queries[i] = { x,i };
	}
	sort(all(queries));
	reverse(all(queries));

	int j = 0;
	p2 best = { 0, n };
	auto add = [&](int island_ind)
	{
		cnt[island_ind]++;
		best = max(best, p2(cnt[island_ind], island_ind + 1));
	};
	for (auto [a, i] : queries)
	{
		while (j<sz(islands) && islands[j].first >= a)
		{
			add(islands[j].second);
			j++;
		}
		ans[i] = best.second;
	}
	rep(i, q)
	{
		cout << ans[i] << '\n';
	}

    return 0;
}
