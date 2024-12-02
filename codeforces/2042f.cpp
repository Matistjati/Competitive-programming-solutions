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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Fenwick
{
	vi tree;
	Fenwick(int n) : tree(n + 1) {}

	void update(int i, int v)
	{
		for (i++; i < tree.size(); i += i & -i)
			tree[i] += v;
	}

	int query(int r)
	{
		int ret = 0;
		for (r++; r > 0; r -= r & -r)
			ret += tree[r];
		return ret;
	}

	int sum(int l, int r)
	{
		if (l) l = query(l - 1);
		return query(r) - l;
	}
};

vi A, B;
Fenwick prefa(1);
struct node
{
    int max_pref_plusb, max_suf_plusb;
    int max_two, max_one;
	int max_two_l; // one incomplete interval at left, complete at right
	int max_two_r; // one incomplete interval right, complete at left
	int max_incomplete; // incomplete at both ends
	int l, r;

    node(int i)
    {
        max_pref_plusb = A[i]+B[i];
        max_suf_plusb = A[i]+B[i];
        max_two = -inf;
        max_two_l = -inf;
        max_two_r = -inf;
		max_incomplete = -inf;
        max_one = A[i]+2*B[i];
		l = r = i;
    }
};


struct Tree
{
	node unit = node(0);
	int n;
	vector<node> tree;
	Tree(int n) : n(n)
	{
		unit.max_one = inf;
		tree.resize(n * 4, unit);
	}

	node merge(node a, node b)
	{
		if (a.max_one == inf) return b;
		if (b.max_one == inf) return a;
		node ret(0);


		ret.l = a.l;
		ret.r = b.r;

		ret.max_one = max({ a.max_one, b.max_one, a.max_suf_plusb + b.max_pref_plusb });
		ret.max_two = max({ a.max_two, b.max_two, a.max_one + b.max_one,
			a.max_two_r + b.max_pref_plusb, b.max_two_l + a.max_suf_plusb });

		ret.max_incomplete = max({ a.max_incomplete + prefa.sum(b.l,b.r), b.max_incomplete + prefa.sum(a.l,a.r),
			a.max_pref_plusb+b.max_suf_plusb});

		ret.max_pref_plusb = max(a.max_pref_plusb, b.max_pref_plusb + prefa.sum(a.l, a.r));
		ret.max_suf_plusb = max(b.max_suf_plusb, a.max_suf_plusb + prefa.sum(b.l, b.r));

		ret.max_two_l = max({ a.max_two_l, prefa.sum(a.l, a.r) + b.max_two_l,
			a.max_pref_plusb+b.max_one, a.max_incomplete+b.max_pref_plusb});

		ret.max_two_r = max({ b.max_two_r, prefa.sum(b.l, b.r) + a.max_two_r,
			b.max_suf_plusb+a.max_one, b.max_incomplete + a.max_suf_plusb});

		node r = ret;
		return r;
	}

	void update(int x, int l, int r, int i, node v)
	{
		if (l == r) tree[x] = v;
		else
		{
			int mid = (l + r) / 2;
			if (i <= mid) update(x * 2, l, mid, i, v);
			else update(x * 2 + 1, mid + 1, r, i, v);
			tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
		}
	}

	void update(int i, node v) { update(1, 0, n - 1, i, v); }

	node query(int x, int l, int r, int ql, int qr)
	{
		if (l > qr || r < ql) return unit;
		if (l >= ql && r <= qr) return tree[x];

		int mid = (l + r) / 2;
		return merge(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
	}

	node query(int ql, int qr) { return query(1, 0, n - 1, ql, qr); }
};

signed main()
{
    fast();

    int n;
    cin >> n;
	A.resize(n);
	B.resize(n);
	rep(i, n) cin >> A[i];
	rep(i, n) cin >> B[i];

	prefa = Fenwick(n);
	rep(i, n) prefa.update(i, A[i]);
	Tree tree(n);

	rep(i, n)
	{
		tree.update(i, node(i));
	}

	int q;
	cin >> q;
	while (q--)
	{
		int t, a, b;
		cin >> t >> a >> b;

		if (t==1)
		{
			a--;
			prefa.update(a, -A[a]);
			A[a] = b;
			prefa.update(a, A[a]);
			tree.update(a, node(a));
		}
		if (t==2)
		{
			a--;
			B[a] = b;
			tree.update(a, node(a));
		}
		if (t==3)
		{
			a--; b--;
			cout << tree.query(a, b).max_two << "\n";
		}
	}



    return 0;
}
