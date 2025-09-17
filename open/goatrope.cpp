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

	p2 g, a, b;
	cin >> g.first >> g.second >> a.first >> a.second >> b.first >> b.second;

	auto d = [&](double a, double b)
		{
			double dx = g.first - a;
			double dy = g.second - b;
			return dx * dx + dy * dy;
		};

	double epsilon = 1e-4;
	double ans = inf;
	for (double p = a.first; p < b.first; p += epsilon) ans = min(ans, d(p, a.second));
	for (double p = a.first; p < b.first; p += epsilon) ans = min(ans, d(p, b.second));
	for (double p = a.second; p < b.second; p += epsilon) ans = min(ans, d(a.first, p));
	for (double p = a.second; p < b.second; p += epsilon) ans = min(ans, d(b.first, p));
	cout << fixed << setprecision(15) << sqrt(ans) << '\n';

	return 0;
}
