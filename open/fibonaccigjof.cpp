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
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif


int mod = int(1e9 + 7);


struct matrix
{
	int a, b, c, d;
	matrix(int a, int b, int c, int d) : a(a),b(b),c(c),d(d) {}
	

	matrix operator*(const matrix& other)
	{
		ll _a = a * other.a + b * other.c;
		ll _b = a * other.b + b * other.d;
		ll _c = c * other.a + d * other.c;
		ll _d = c * other.b + d * other.d;
		_a %= mod; _b %= mod; _c %= mod; _d %= mod;
		return matrix(_a,_b,_c,_d);
	}

	static matrix pow_unitfib(int p)
	{
		matrix ret(1, 0, 0, 1);
		matrix accum(1, 1, 1, 0);
		while (p)
		{
			if (p % 2) ret = ret * accum;
			accum = accum * accum;
			p >>= 1;
		}
		return ret;
	}

	matrix operator+(const matrix& other)
	{
		ll _a = a + other.a;
		ll _b = b + other.b;
		ll _c = c + other.c;
		ll _d = d + other.d;
		_a %= mod; _b %= mod; _c %= mod; _d %= mod;
		return matrix(_a, _b, _c, _d);
	}
};
matrix fibmat(1,1,1,0);

struct Tree
{
	vector<matrix> tree;
	vi lazy;

	Tree(int n) : tree(n*4,fibmat), lazy(n*4) {}

	void push(int x)
	{
		if (!lazy[x]) return;
		matrix ld = matrix::pow_unitfib(lazy[x]);
		tree[x * 2] = tree[x * 2] * ld;
		tree[x * 2+1] = tree[x * 2+1] * ld;

		lazy[x * 2] += lazy[x];
		lazy[x * 2+1] += lazy[x];
		lazy[x] = 0;
	}

	void update(int x, int l, int r, int ql, int qr, int d, const matrix& dm)
	{
		if (l > qr || r < ql) return;
		if (l>=ql&&r<=qr)
		{
			tree[x] = tree[x] * dm;
			lazy[x] += d;
			return;
		}
		push(x);

		int mid = (l + r) / 2;
		update(x * 2, l, mid, ql, qr, d, dm);
		update(x * 2 + 1, mid + 1, r, ql, qr, d, dm);
		tree[x] = tree[x * 2] + tree[x * 2 + 1];
	}

	int query(int x, int l, int r, int ql, int qr)
	{
		if (l > qr || r < ql) return 0;
		if (l >= ql && r <= qr) return tree[x].c;
		push(x);
		int mid = (l + r) / 2;
		return (query(x*2,l,mid,ql,qr)+query(x*2+1,mid+1,r,ql,qr)) % mod;
	}
};

signed main()
{
	fast();


	int n, q;
	cin >> n >> q;

	Tree tree(n);
	rep(i, n)
	{
		int v;
		cin >> v;
		v--;
		tree.update(1, 0, n - 1, i, i, v, matrix::pow_unitfib(v));
	}

	ofstream out;
	while (q--)
	{
		int t;
		cin >> t;
		if (t==1)
		{
			int l, r, d;
			cin >> l >> r >> d;
			l--; r--;
			tree.update(1, 0, n - 1, l, r, d, matrix::pow_unitfib(d));
		}
		else
		{
			int l, r;
			cin >> l >> r;
			l--; r--;
			cout << tree.query(1, 0, n - 1, l, r) << "\n";
		}
	}

	return 0;
}
