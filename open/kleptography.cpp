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

	int n, m;
	cin >> n >> m;

	string a, b;
	cin >> a >> b;

	string ans=a;
	reverse(all(ans));
	while (sz(b)>n)
	{
		string endd;
		rep(i, n) endd.push_back(b.back()), b.pop_back();
		reverse(all(endd));

		string gotten;
		rep(i, n)
		{
			gotten.push_back(((int(endd[i] - 'a')) - int(a[i] - 'a') + 26) % 26 + 'a');
		}
		a = gotten;
		reverse(all(gotten));
		ans += gotten;
		//cout << gotten << '\n';
	}
	int extra = sz(ans) - m;
	rep(i, extra)ans.pop_back();
	reverse(all(ans));
	cout << ans;



	return 0;
}
