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

	vector<pair<int, string>> cups;
	int n;
	cin >> n;
	rep(i, n)
	{
		string a, b;
		cin >> a >> b;
		if (a[0] > '0' && a[0] <= '9')
		{
			cups.emplace_back(stoi(a), b);
		}
		else cups.emplace_back(2 * stoi(b), a);
	}
	sort(all(cups));
	repe(c, cups) cout << c.second << '\n';

	return 0;
}
