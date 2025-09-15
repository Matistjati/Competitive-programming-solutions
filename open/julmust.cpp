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
	cin >> x;
	int lo = -1;
	int hi = x+1;
	int i = 1;
	while (1)
	{
		int mid = (lo + hi) / 2;
		cout << mid*i++ << endl;
		string resp;
		cin >> resp;
		if (resp=="exact")
		{
			break;
		}
		if (resp == "less") hi = mid;
		else lo = mid;
	}

	return 0;
}
