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
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

void solve()
{
	int n;
	cin >> n;

	vi nums(n);
	rep(i, n) cin >> nums[i];
	reverse(all(nums));
	while (nums.size() && nums.back() == 0) nums.pop_back();
	while (nums.size() && nums.back() == 1) nums.pop_back();
	reverse(all(nums));
	while (nums.size() && nums.back() == 0) nums.pop_back();

	int ans = 0;
	n = nums.size();
	rep(i, n)if (nums[i] == 0) ans++;
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
