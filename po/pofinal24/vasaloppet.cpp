// slow, but obviously correct. I don't want to deal with off-by-one errors
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
#define per(i, high) for (int i = high-1; i >= 0; i--)

#if _MSC_VER > 0
#define deb __debugbreak();
#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
#define clz(x) _lzcnt_u32(x)
#else
#define clz(x) __builtin_clz(x)
#define deb ;
#define popcount(x) __builtin_popcountll(x)
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#ifdef _DEBUG
#define debassert(expr) if(!(expr)) deb;
#else
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };


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

	Node* root = new Node(0, int(1e9 + 10));

	int n, t, s;
	cin >> n >> t >> s;

	vi leftp;
	rep(i, n)
	{
		int l, r;
		cin >> l >> r;
		leftp.push_back(l);
		root->add(l, r - 1, 1); // add 1 to [l,r]
	}

	int ans = 0;
	rep(i, n)
	{
		int u = leftp[i];
		if (u > t) continue;
		ans = max(ans, root->query(u, u + s - 1)); // query [u,u+s-1]
	}
	cout << s - ans << endl;
	_Exit(0); // leaky leaky

	//return 0;
}
