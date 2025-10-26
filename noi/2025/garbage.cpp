#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

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

struct Tree
{
	vi tree;
	vi lazy;
	Tree(int n) : tree(n*4),lazy(n*4) {}

	void put_node(int x, int v)
	{
		tree[x] += v;
		lazy[x] += v;
	}
	void push(int x)
	{
		put_node(x * 2, lazy[x]);
		put_node(x * 2+1, lazy[x]);
		lazy[x] = 0;
	}

	void update(int x, int l, int r, int ql, int qr, int v)
	{
		if (r < ql || l > qr) return;
		if (l >= ql && r <= qr)
		{
			return put_node(x, v);
		}
		push(x);
		int mid = (l + r) / 2;
		update(x * 2, l, mid, ql, qr, v);
		update(x * 2 + 1, mid + 1, r, ql, qr, v);
		tree[x] = max(tree[x * 2], tree[x * 2 + 1]);
	}

	int getmax()
	{
		return tree[1];
	}
};

signed main()
{
	fast();


	int n, w, h;
	cin >> n >> w >> h;
	Tree tree(n);

	vector<array<int, 3>> trash(n);
	vi xcoord;
	rep(i, n)
	{
		int x, y, w;
		cin >> x >> y >> w;
		trash[i] = { x,y,w };
		xcoord.push_back(x);
	}
	sort(all(xcoord));
	sort(all(trash), [](array<int, 3> a, array<int, 3> b)
		{
			return a[1] < b[1];
		});

	int ans = 0;
	int p = 0;
	rep(i, n)
	{
		while (p<n&&trash[i][1] + h - 1 >= trash[p][1])
		{
			int lpos = lower_bound(all(xcoord), trash[p][0] - w + 1) - begin(xcoord);
			int rpos = prev(upper_bound(all(xcoord), trash[p][0])) - begin(xcoord);
			tree.update(1, 0, n - 1, lpos,rpos,trash[p][2]);
			p++;
		}

		ans = max(ans, tree.getmax());
		int myx = trash[i][0];
		int lpos = lower_bound(all(xcoord), myx - w + 1) - begin(xcoord);
		int rpos = prev(upper_bound(all(xcoord), myx)) - begin(xcoord);
		tree.update(1, 0, n - 1, lpos, rpos, -trash[i][2]);
	}
	cout << ans;

	return 0;
}
