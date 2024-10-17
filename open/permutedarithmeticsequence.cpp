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

	auto isgood = [](vi nums)
	{
		int d = nums[1] - nums[0];
		bool good = 1;
		repp(i, 1, sz(nums))
		{
			good &= nums[i] == nums[0] + d * i;
		}
		return good;
	};

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		if (n==1)
		{
			cout << "arithmetic\n";
			continue;
		}
		vi nums(n);
		rep(i, n) cin >> nums[i];
		if (isgood(nums)) 
		{
			cout << "arithmetic\n";
			continue;
		}
		sort(all(nums));
		if (isgood(nums))
		{
			cout << "permuted arithmetic\n";
			continue;
		}
		cout << "non-arithmetic\n";
	}

	return 0;
}
