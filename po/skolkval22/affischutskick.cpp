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

	int a, b, c;
	cin >> a >> b >> c;

	double ans = 2 * 229 * 324 / 1e6 * a + 2 * 297 * 420 / 1e6 * b + 210 * 297 / 1e6 * c;
	cout << fixed << setprecision(15) << ans << '\n';

	return 0;
}
