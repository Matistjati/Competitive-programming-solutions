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
	vi a(n), b(n);
	repe(v, a) cin >> v;
	repe(v, b) cin >> v;

	vi ans(n*2);

	rep(i, n)
	{
		int v = a[i];
		int num_win = upper_bound(all(b), v) - begin(b);
		ans[n-i]++;
		ans[n-i + num_win]--;
	}
	repp(i, 1, 2 * n) ans[i] += ans[i - 1];
	rep(i, n) ans[i] += ans[i + n];

	int cnt = 0;
	rep(i, n) cnt += ans[i] == n;
	cout << cnt << '\n';

	return 0;
}
