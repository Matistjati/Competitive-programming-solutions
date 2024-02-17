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
};


struct Tree
{
	vector<segment> tree;
	Tree(int n) : tree(n * 4) {}

	segment merge(segment left, segment right)
	{

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

	void update(int x, int l, int r, int i, int v)
	{
		if (l == r) tree[x] = segment({ v > 0 ? v : 0,v > 0 ? v : 0,v, v });
		else
		{
			int mid = (l + r) / 2;
			if (i <= mid) update(x * 2, l, mid, i, v);
			else update(x * 2 + 1, mid + 1, r, i, v);
			tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
		}
	}
};

signed main()
{
	fast();

	int n, q;
	cin >> n >> q;
	vi nums(n);
	rep(i, n) cin >> nums[i];

	Tree tree(n);
	rep(i, n) tree.update(1, 0, n - 1, i, nums[i]);

	while (q--)
	{
		int i, v;
		cin >> i >> v;
		i--;
		tree.update(1, 0, n - 1, i, v);
		cout << max(0LL, tree.tree[1].bestsum) << "\n";
	}

	return 0;
}
