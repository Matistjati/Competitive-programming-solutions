#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

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
	set<string> items;
	rep(i, m)
	{
		string x;
		cin >> x;
		items.insert(x);
	}
	rep(i, n - 1)
	{
		set<string> isect;
		rep(j, m)
		{
			string x;
			cin >> x;
			if (items.count(x)) isect.insert(x);
		}
		items = isect;
	}
	cout << sz(items) << '\n';
	repe(item, items) cout << item << '\n';

	return 0;
}
