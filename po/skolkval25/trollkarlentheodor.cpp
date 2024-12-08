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

	int n, dmgone, dmgall;
	cin >> n >> dmgone >> dmgall;
	vi hp(n);
	rep(i, n) cin >> hp[i];


	int lo = -1;
	int hi = int(1e10)+10; // carefully chosen hi gives AC and no overflow
	// ans is bounded by 1e9 * n = 1e10
	// first iteration of binary search, we get 1e9/2*1e10, which fits in ll
	// then, if A is large, we will get smaller mid

	while (lo+1<hi)
	{
		int mid = (lo + hi) / 2;

		int uses = 0;
		rep(i, n)
		{
			int h = hp[i];
			h -= dmgall * mid;
			if (h > 0)
			{
				uses += (h + dmgone - 1) / dmgone;
			}
		}
		if (uses <= mid) hi = mid;
		else lo = mid;
	}
	cout << hi;

	return 0;
}
