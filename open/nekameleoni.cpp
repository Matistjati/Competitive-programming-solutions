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

int k;
typedef bitset<51> vb;
struct segment
{
	vb seen;
	vector<p2> lnum, rnum;
	int cost;
};

segment merge(segment l, segment r)
{
	int newcost = inf;
	int numon = 0;
	vi oncnt(51);
	repe(v, l.rnum) oncnt[v.second]++;
	rep(i, 51) if (oncnt[i])numon++;
	int j = sz(l.rnum) - 1;
	int i = 0;
	while (j >= 0)
	{
		while (i < sz(r.lnum) && numon < k)
		{
			if (oncnt[r.lnum[i].second] == 0) numon++;
			oncnt[r.lnum[i].second]++;
			i++;
		}

		if (numon == k)
		{
			int hi = i ? r.lnum[i - 1].first : inf;
			newcost = min(newcost, hi - l.rnum[j].first + 1);
		}

		if (oncnt[l.rnum[j].second] == 1) numon--;
		oncnt[l.rnum[j].second]--;
		j--;
	}

	l.cost = min(l.cost, r.cost);
	l.cost = min(l.cost, newcost);
	repe(v, r.lnum) if (!l.seen[v.second]) l.lnum.push_back(v);
	repe(v, l.rnum) if (!r.seen[v.second]) r.rnum.push_back(v);
	l.rnum = r.rnum;

	l.seen |= r.seen;
	return l;
}

struct Tree
{
	vector<segment> tree;
	Tree(int n) : tree(n * 4) {}

	void update(int x, int l, int r, int i, int v)
	{
		if (l == r)
		{
			segment ret = { vb(), {},{}, inf };
			ret.seen[v] = 1;
			ret.lnum.emplace_back(l, v);
			ret.rnum.emplace_back(l, v);
			tree[x] = ret;
			return;
		}

		int mid = (l + r) / 2;
		if (i <= mid) update(x * 2, l, mid, i, v);
		else update(x * 2 + 1, mid + 1, r, i, v);

		tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
	}
};

signed main()
{
	fast();

	int n, q;
	cin >> n >> k >> q;
	vi nums(n);
	rep(i, n) cin >> nums[i];
	Tree tree(n);
	rep(i, n)
	{
		tree.update(1, 0, n - 1, i, nums[i]);
	}
	while (q--)
	{
		int t;
		cin >> t;
		if (t == 1)
		{
			int i, v;
			cin >> i >> v;
			i--;
			tree.update(1, 0, n - 1, i, v);
		}
		else
		{
			int v = tree.tree[1].cost;
			cout << (v == inf ? -1 : v) << "\n";
		}
	}


	return 0;
}
