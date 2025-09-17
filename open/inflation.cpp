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

	int n;
	cin >> n;
	vi nums(n);
	repe(v, nums) cin >> v;
	sort(all(nums));
	double v = 1;
	rep(i, n)
	{
		if (nums[i]>(i+1))
		{
			cout << "impossible\n";
			return 0;
		}
		v = min(v, double(nums[i]) / (i+1));
	}
	cout << fixed << setprecision(15) << v << '\n';

	return 0;
}
