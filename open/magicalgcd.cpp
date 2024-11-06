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

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vi nums(n);
		rep(i, n) cin >> nums[i];
		map<int,int> waiting;
		int ans = max(n, *max_element(all(nums)));
		rep(i, n)
		{
			map<int,int> neww;
			repe(u, waiting)
			{
				int g = gcd(u.first, nums[i]);
				if (g > 1)
				{
					neww[g] = max(neww[g], u.second + 1);
					ans = max(ans, g * (u.second+1));
				}
			}
			neww[nums[i]] = max(neww[nums[i]], 1LL);
			waiting = neww;
		}
		cout << ans << "\n";
	}

	return 0;
}
