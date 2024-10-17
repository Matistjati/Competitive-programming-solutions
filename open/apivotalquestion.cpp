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

	int n;
	cin >> n;
	vi nums(n);
	rep(i, n) cin >> nums[i];
	vi prefmax(n);
	vi sufmin(n);

	int m = -1;
	rep(i, n)
	{
		prefmax[i] = m;
		m = max(m, nums[i]);
	}

	m = inf;
	for (int i = n - 1; i >= 0; i--)
	{
		sufmin[i] = m;
		m = min(m, nums[i]);
	}

	vi which;
	int ans = 0;
	rep(i, n)
	{
		
		if (prefmax[i]<nums[i] && sufmin[i]>nums[i])
		{
			ans++;
			which.push_back(nums[i]);
		}
	}
	cout << ans << " ";
	rep(i, min(100LL, sz(which))) cout << which[i] << " ";

	return 0;
}
