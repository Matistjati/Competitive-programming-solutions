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

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	bool first = 1;
	while (cin >> n && n) {
		first = 0;
		vector<pair<int,double>> vehicles(n);
		rep(i, n) cin >> vehicles[i].second, vehicles[i].first=i;

		mt19937 rng(10);

		double t = 0;
		repe(v, vehicles) t += v.second;
		t /= 2;
		vi sol;
		double best = -1;

		rep(i, 1000)
		{
			vi taken;
			double tot = 0;
			shuffle(all(vehicles), rng);
			rep(j, n)
			{
				if (tot+vehicles[j].second<=t)
				{
					tot += vehicles[j].second;
					taken.push_back(vehicles[j].first);
				}
			}
			if (tot>best)
			{
				best = tot;
				sol = taken;
			}
		}
		rep(i, sz(sol))
		{
			cout << sol[i] + 1;
			if (i + 1 != sz(sol)) cout << " ";
		}
		cout << '\n';
	}

	return 0;
}
