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

struct Tree
{
	vector<vi> pref;
	vector<vi> occs;
	vi tree;
	Tree(vi& nums) : pref(sz(nums) * 4), occs(sz(nums) * 4), tree(sz(nums) * 4)
	{
		build(1, 0, sz(nums) - 1, nums);
	}

	void build(int x, int l, int r, vi& nums)
	{
		if (l == r)
		{
			occs[x] = { nums[l] };
			pref[x] = { nums[l] };
			return;
		}
		vi seg;
		repp(i, l, r + 1) seg.push_back(nums[i]);

		int cost = 0;
		int m = -1;
		rep(i, sz(seg))
		{
			if (seg[i] < m) cost += m - seg[i], seg[i] = m;
			m = max(m, seg[i]);
		}
		occs[x] = seg;
		repp(i, 1, sz(seg)) seg[i] += seg[i - 1];
		pref[x] = seg;

		int mid = (l + r) / 2;
		build(x * 2, l, mid, nums);
		build(x * 2 + 1, mid + 1, r, nums);

		tree[x] = cost;
	}

	int normalize(int x, int by)
	{
		int cost = tree[x];

		auto it = upper_bound(occs[x].begin(), occs[x].end(), by);
		if (it != occs[x].begin())
		{
			int p = (it - occs[x].begin()) - 1;
			cost += (p + 1) * by - pref[x][p];
		}
		return cost;
	}

	p2 query(int x, int l, int r, int ql, int qr, int by)
	{
		if (l > qr || r < ql) return p2(0, -inf);
		if (l >= ql && r <= qr) return p2(normalize(x, by), max(occs[x].back(), by));
		int mid = (l + r) / 2;
		p2 ret = query(x * 2, l, mid, ql, qr, by);
		p2 right = query(x * 2 + 1, mid + 1, r, ql, qr, ret.second);
		return p2(ret.first + right.first, right.second);
	}
};

signed main()
{
	fast();

	int n, q;
	cin >> n >> q;
	vi nums(n);
	rep(i, n)cin >> nums[i];
	Tree tree(nums);
	while (q--)
	{
		int l, r;
		cin >> l >> r;
		l--; r--;
		cout << tree.query(1, 0, n - 1, l, r, -1).first << "\n";
	}


	return 0;
}
