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

	int num_good = 0;
	string font;
	cin >> font;
	num_good += font == "monospace";
	int d1 = 0, d2 = 0;
	int a, b, c;
	cin >> a >> b >> c;
	d1 += a + b + c;
	cin >> a >> b >> c;
	d2 = a + c + 255 - b;
	num_good += d1 <= 25;
	num_good += d2 <= 35;
	cout << (num_good >= 2 ? "L33T H4X0R" : "n00b") << '\n';

	return 0;
}
