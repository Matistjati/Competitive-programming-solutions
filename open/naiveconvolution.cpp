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
	vi a(n), b(m);
	repe(v, a) cin >> v;
	repe(v, b) cin >> v;
	vector<__int128_t> res(n + m - 1);

	rep(i, sz(a))
	{
		rep(j, sz(b))
		{
			res[i + j] += __int128_t(a[i]) * b[j];
		}
	}

	while (sz(res)>1 && res.back() == 0) res.pop_back();
	repe(x, res)
	{
		bool negative = x < 0;
		if (x < 0) x = -x;
		string s;
		while (x) s.push_back((x % 10) + '0'), x /= 10;
		if (s.empty()) s = "0";
		if (negative) s.push_back('-');
		reverse(all(s));
		cout << s << " ";
	}

    return 0;
}
