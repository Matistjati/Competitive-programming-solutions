// O(C^2*100) (the 100 is more like C+const)
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

	ll r, c;
	cin >> r >> c;
	vi start_val(c);
	repe(v, start_val) cin >> v;
	p2 start, goal;
	cin >> start.second >> start.first >> goal.second >> goal.first;

	if (start.first > goal.first)
	{
		swap(start, goal);
	}
	if (start.second < goal.second) // probably not needed
	{
		start.second = c - 1 - start.second;
		goal.second = c - 1 - goal.second;
		reverse(all(start_val));
	}
	assert(start.first <= goal.first);
	assert(start.second >= goal.second);


	auto cost_at = [&](p2 p)
	{
		return start_val[p.second] - p.first;
	};


	auto vertical_cost = [&](ll row1, ll row2, ll col)
	{
		if (abs(row1 - row2) < 2) return 0LL;

		ll low = min(row1, row2);
		ll high = max(row1, row2);
		ll dist = high - low - 1;

		return dist * start_val[col] - (dist * (low + high)) / 2;
	};

	ll ans = inf;
	rep(col1, c)
	{
		// first, walk to col1 horizontally
		set<p2> horizontal_costs;
		repp(i, min(col1, start.second), max(col1, start.second) + 1)
		{
			horizontal_costs.insert(p2(start.first, i));
		}

		repp(row1, max(0LL, goal.first - 100), min(r, goal.first + 100))
		{
			ll vert1 = vertical_cost(start.first, row1, col1);

			// we are now at (row1,col1)
			rep(col2, c)
			{
				set<p2> horizontal_costs_2;
				repp(i, min(col1, col2), max(col1, col2) + 1)
				{
					horizontal_costs_2.insert(p2(row1, i));
				}
				// we are now at (row1,col2)

				ll vert2 = vertical_cost(goal.first, row1, col2);

				// we are now at (goal.first, col2)
				set<p2> horizontal_costs_3;

				repp(i, min(col2, goal.second), max(col2, goal.second) + 1)
				{
					horizontal_costs_3.insert(p2(goal.first, i));
				}

				ll final_cost = vert1 + vert2;
				set<p2> horizontals = horizontal_costs;
				horizontals.insert(all(horizontal_costs_2));
				horizontals.insert(all(horizontal_costs_3));
				repe(p, horizontals) final_cost += cost_at(p);
				ans = min(ans, final_cost);
			}
		}
	}
	cout << ans << '\n';

	return 0;
}
