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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


struct Node
{
	Node* lchild;
	Node* rchild;
	int l, r;
	int sum;
	int lazy;

	Node(int l, int r) : lchild(nullptr), rchild(nullptr), l(l), r(r), sum(0), lazy(0) {}

	void push()
	{
		int mid = (l + r) / 2;
		if (!lchild)
		{
			lchild = new Node(l, mid);
			rchild = new Node(mid + 1, r);
		}
		lchild->sum = lchild->sum + lazy * (mid - l + 1);
		lchild->lazy = lchild->lazy + lazy;

		rchild->sum = rchild->sum + lazy * (r - (mid + 1) + 1);
		rchild->lazy = rchild->lazy + lazy;
		lazy = 0;
	}

	void add(int ql, int qr, int v)
	{
		if (l > qr || r < ql) return;
		if (l >= ql && r <= qr)
		{
			sum = sum + v * (r - l + 1);
			lazy = lazy + v;
		}
		else
		{
			push();
			lchild->add(ql, qr, v);
			rchild->add(ql, qr, v);
			sum = rchild->sum + lchild->sum;
		}
	}

	int query(int ql, int qr)
	{
		if (l > qr || r < ql) return 0;
		if (l >= ql && r <= qr) return sum;
		else
		{
			push();
			return lchild->query(ql, qr) + rchild->query(ql, qr);
		}
	}
};

signed main()
{
	fast();

	int n, m;
	cin >> n >> m;

	vi pos(n);
	vi mult(n);
	rep(i, n)
	{
		string name;
		cin >> name >> pos[i];
		mult[i] = (name == "Joshua" || name == "Gustav") ? 2 : 1;
	}

	Node* root = new Node(0, int(1e9));
	rep(i, m)
	{
		int l, r;
		cin >> l >> r;
		root->add(l, r, 1);
	}

	int ans = 0;
	rep(i, n)
	{
		ans += mult[i] * (root->query(pos[i], pos[i]) == 0);
	}

	cout << ans;

	return 0;
}
