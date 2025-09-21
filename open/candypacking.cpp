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

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	ll n, k;
	cin >> n >> k;
	vi candies(n);
	repe(v, candies) cin >> v;
	ll tot_candies = accumulate(all(candies), 0LL);
	ll num_boxes = tot_candies / k;
	if (num_boxes==0)
	{
		cout << "0 0\n";
		return 0;
	}

	ll cost;
	if (num_boxes==1)
	{
		if (n==1)
		{
			ll v = candies[0];
			if (v == k) cost = candies[0] - 1; // we have to make them all unique to satisfy not using all of a kind
			else cost = 1; // save one not on pile to make sure dont use all of them. then transform one so there are different candies
		}
		else
		{
			cost = 0;
			sort(all(candies));
			reverse(all(candies));
			// no risk for monochromatic pile
			// start off by saving one of each type, then place rest on pile
			ll num_candies = tot_candies-n;
			// if we need more than this, we have to make all but one unique in each group
			while (num_candies < k)
			{
				cost += candies.back() - 1;
				num_candies++;
				candies.pop_back();
			}
		}
	}
	else
	{
		ll m = *max_element(all(candies));
		if (m<=num_boxes) // constraint 1 is never violated, just place em
		{
			cost = 0;
		}
		else
		{
			ll ind = max_element(all(candies))-begin(candies);
			ll other_sum = 0;
			rep(i, n) if (i != ind) other_sum += candies[i];
			if (other_sum+num_boxes>=k*num_boxes) // take one row of the largest one. constraint 1 fine, 2 probably fine
			{
				cost = 0;
			}
			else
			{
				if (other_sum>=num_boxes) // largest one is huge
				{
					cost = 0;
				}
				else // take some of the largest one and make them unique
				{
					cost = num_boxes - other_sum;
				}
			}
		}
	}

	cout << num_boxes << " " << cost << '\n';

	return 0;
}
