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

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	ll n, k;
	cin >> n >> k;
	map<string, ll> stats;
	rep(i, n)
	{
		string name;
		ll val;
		cin >> name >> val;
		stats[name] = val;
	}

	ll e;
	cin >> e;
	map<string, map<ll,ll>> eventvals;
	map<string, ll> eventcount;
	rep(i, e)
	{
		string name;
		ll val;
		cin >> name >> val;
		eventvals[name][val]++;
		eventcount[name]++;
	}

	repe(e, eventvals)
	{
		ll myval = stats[e.first];

		ll m = 0;
		repe(u, e.second) m = max(m, u.first);
		if (myval<m)
		{
			ll delta = m - myval;
			myval += delta;
			k -= delta;
		}
		stats[e.first] = myval;
	}

	if (k<0)
	{
		cout << '0';
		return 0;
	}

	priority_queue<pair<ll,string>> num_edging;
	ll most_good = 0;
	repe(e, eventvals)
	{
		ll myval = stats[e.first];

		ll cnt = e.second[myval];
		most_good = max(most_good, eventcount[e.first]);
		if (cnt)
		{
			num_edging.emplace(myval * cnt+eventcount[e.first], e.first);
		}
	}
	while (sz(num_edging))
	{
		if (k == 0) break;
		auto [_, attribute] = num_edging.top();
		if (_ < most_good) break;
		num_edging.pop();
		stats[attribute]++;
		k--;

		ll myval = stats[attribute];

		ll cnt = eventvals[attribute][myval];
		if (cnt)
		{
			num_edging.emplace(myval * cnt + eventcount[attribute], attribute);
		}
	}

	ll ans = 0;
	repe(e, eventvals)
	{
		ll myval = stats[e.first];

		for (auto [v, cnt] : e.second)
		{
			assert(myval >= v);
			if (myval == v) ans += 0;
			else ans += cnt * myval;
		}
	}
	cout << ans+most_good*k << '\n';

	return 0;
}
