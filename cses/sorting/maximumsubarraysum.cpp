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

struct segment
{
	ll bestprefix, bestsuffix, bestsum, tot;
	bool usedany;
};

segment solve(int l, int r, vi& nums)
{
	if (l == r)
	{
		int v = nums[l];
		return segment({ v > 0 ? v : 0,v > 0 ? v : 0,v, v, 0 });
	}

	int mid = (l + r) / 2;
	segment left = solve(l, mid, nums);
	segment right = solve(mid + 1, r, nums);

	segment ret;
	ret.bestprefix = max(left.bestprefix, right.bestprefix + left.tot);
	ret.bestsuffix = max(right.bestsuffix, left.bestsuffix + right.tot);
	ret.tot = left.tot + right.tot;
	ret.bestsum = max(left.bestsum, right.bestsum);
	ret.bestsum = max(ret.bestsum, left.bestsuffix + right.bestprefix);
	ret.bestsum = max(ret.bestsum, ret.bestprefix);
	ret.bestsum = max(ret.bestsum, ret.bestsuffix);

	return ret;
}

signed main()
{
	fast();

	int n;
	cin >> n;
	vi nums(n);
	rep(i, n) cin >> nums[i];
	bool allneg = 1;
	rep(i, n) allneg &= nums[i] < 0;
	if (allneg) cout << *max_element(nums.begin(), nums.end());
	else cout << solve(0, n - 1, nums).bestsum;

	return 0;
}
