#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
	fast();

	int l, r;
	cin >> l >> r;
	int ans = 0;
	repp(i, l, r + 1)
	{
		string d = to_string(i);
		if (d.find('0') != string::npos) continue;
		set<char> seen;
		bool good = 1;
		repe(c, d)
		{
			good &= seen.find(c) == seen.end();
			seen.insert(c);
			good &= i % (c - '0') == 0;
		}
		if (!good) continue;
		ans++;
	}
	cout << ans;

	return 0;
}
