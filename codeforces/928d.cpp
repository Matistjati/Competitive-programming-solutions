#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

void solve()
{
	int n;
	cin >> n;

	multiset<int> nums;
	rep(i, n)
	{
		int v;
		cin >> v;
		nums.insert(v);
	}

	auto inverse = [](int v)
	{
		int ret = 0;
		rep(i, 31) if ((v & (1LL << i)) == 0) ret += 1LL << i;
		return ret;
	};

	int ans = 0;
	while (nums.size())
	{
		int k = *nums.begin();
		nums.erase(nums.begin());
		int inv = inverse(k);
		auto it = nums.find(inv);
		if (it != nums.end())
		{
			nums.erase(it);
		}
		ans++;
	}
	cout << ans << "\n";
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
