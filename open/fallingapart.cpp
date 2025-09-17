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
	reverse(all(nums));

	int a=0, b=0;
	for (int i = 0; i < n; i += 2)
	{
		a += nums[i];
		if (i + 1 < n) b += nums[i + 1];
	}

	cout << a << " " << b << '\n';

	return 0;
}
