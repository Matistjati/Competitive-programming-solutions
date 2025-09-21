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

typedef double Real;
typedef complex<Real> cp;
int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;

		vector<ll> poly(n + 1);
		repe(v, poly) cin >> v;

		if (n == 1)
		{
			cout << int(round(-double(poly[0]) / poly[1])) << '\n';
			continue;
		}
		vector<ll> derivative = poly;
		rep(i, sz(derivative)) derivative[i] *= i;
		derivative.erase(derivative.begin());

		auto eval = [&](Real x, vector<ll>& poly)
			{
				Real ret = 0;
				for (int i = sz(poly) - 1; i >= 0; i--)
				{
					ret = ret * x + poly[i];
				}
				return ret;
			};

		Real curr_guess = 1e5;
		rep(i, 150)
		{
			curr_guess -= eval(curr_guess, poly) / eval(curr_guess, derivative);
		}


		cout << int(round(curr_guess)) << '\n';
	}

	return 0;
}
