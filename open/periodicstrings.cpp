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

	string s;
	cin >> s;
	repp(k, 1, sz(s)+1)
	{
		if (sz(s) % k != 0) continue;
		string f = s.substr(0, k);
		bool good = 1;
		for (int j = k; j < sz(s); j += k)
		{
			f.insert(f.begin(), f.back());
			f.pop_back();
			good &= s.substr(j, k) == f;
		}

		if (good)
		{
			cout << k;
			return 0;
		}
	}

	return 0;
}
