#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }


template<class I> vi lis(const vector<I>& S) {
	if (S.empty()) return {};
	vi prev(sz(S));
	typedef pair<I, int> p;
	vector<p> res;
	repp(i, 0, sz(S)) {
		// change 0 -> i for longest non-decreasing subsequence
		auto it = lower_bound(all(res), p{ S[i], 0 });
		if (it == res.end()) res.emplace_back(), it = res.end() - 1;
		*it = { S[i], i };
		prev[i] = it == res.begin() ? 0 : (it - 1)->second;
	}
	int L = sz(res), cur = res.back().second;
	vi ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
}

signed main()
{
    fast();

	int n, m;
	cin >> n >> m;
	vi occ(n);
	vi nums(n);
	repe(v, nums) cin >> v,v--;
	rep(i, n) occ[nums[i]] = i;

	vi arr2;
	vector<p2> arrows;
	rep(i, m)
	{
		int x;
		cin >> x;
		x--;
		arr2.push_back(x);
		if (x < n) arrows.emplace_back(occ[x], i);
	}
	sort(all(arrows));
	vi arr;
	repe(u, arrows) arr.push_back(u.second);
	vi ans = lis(arr);

	cout << sz(ans) << "\n";
	repe(v, ans)
	{
		cout << arr2[arr[v]]+1 << " ";
	}

    return 0;
}
