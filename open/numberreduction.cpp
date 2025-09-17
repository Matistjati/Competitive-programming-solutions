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

	int x;
	cin >> x;
	int ans = 0;
	while (x>1)
	{
		if (x % 2 == 1) x = 3 * x + 1;
		else x /= 2;
		ans++;
	}
	cout << ans << '\n';

	return 0;
}
