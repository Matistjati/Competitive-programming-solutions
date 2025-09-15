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

	int x;
	string word;
	cin >> x >> word;
	for (int i = x; i > 0; i--)
	{
		cout << i << " bottle" << (i>1?"s":"") << " of " << word << " on the wall, " << i << " bottle" << (i > 1 ? "s" : "") << " of " << word << ".\n";
		cout << "Take " << (i > 1 ? "one" : "it") << " down, pass it around, " << (i==1?"no more":to_string(i-1)) << " bottle" << (i != 2 ? "s" : "") << " of " << word << (i>1?" on the wall":"") << ".\n" << (i>1?"\n":"");
	}

	return 0;
}
