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

const long double E = 2.718281828459045235360287471352L;
template<typename T, int Iterations = 2>
T lambert_w0(T x)
{
	if (x < -(1 / E))
		x = -(1 / E);

	T current = 0;

	for (int i = 0; i < Iterations; i++)
	{
		T cexp = std::exp(current);
		T denom = cexp * (current + 1) - ((current + 2) * (current * cexp - x) / (2 * current + 2));

		current = current - ((current * cexp - x) / denom);
	}

	return current;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	double x;
	cin >> x;


	auto eval = [x](long double v)
		{
			return -lambert_w0<double, 10>(-log(v)) / log(v);
		};

	double lo = 0;
	double hi = pow(E,1/ E)+1e-4;
	rep(i, 100)
	{
		double mid = (lo + hi) / 2;
		if (eval(mid) < x)
		{
			lo = mid;
		}
		else hi = mid;
	}

	pair<long double, double> ans = { inf,inf };
	for (double v = hi-1e-3; v < hi+1e-3; v += 1e-6)
	{
		ans = min(ans, make_pair(abs(x - eval(v)), v));
	}
	cout << fixed << setprecision(15) << ans.second << '\n';

	return 0;
}
