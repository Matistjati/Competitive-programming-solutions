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

void solve()
{
	int n, q;
	cin >> n >> q;
	vi nums(n);
	rep(i, n) cin >> nums[i];

	uniform_int_distribution<int> dist(0, int(1e18));
	mt19937 rng;
	map<int, int> mapping;
	repe(num, nums)
	{
		if (mapping.find(num) == mapping.end()) mapping[num] = dist(rng);
	}
	rep(i, n)nums[i] = mapping[nums[i]];
	vi xorp(nums);
	repp(i, 1, n) xorp[i] ^= xorp[i - 1];
	auto query = [&](int l, int r)
	{
		if (l) l = xorp[l - 1];
		return xorp[r] ^ l;
	};

	while (q--)
	{
		int l, r;
		cin >> l >> r;
		l--; r--;
		cout << (query(l, r) == 0 ? "YES" : "NO") << "\n";
	}
}

signed main()
{
	fast();

	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}

	return 0;
}
