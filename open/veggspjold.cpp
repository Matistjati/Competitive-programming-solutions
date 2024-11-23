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
	Node* lc = 0, * rc = 0;
	int l, r, lazy=0;
	p2 v;
	Node(int l, int r) : l(l), r(r), v(0, r-l+1) {}

	p2 merge(p2 a, p2 b)
	{
		if (a.first == b.first) return p2(a.first, a.second + b.second);
		if (a.first < b.first) return a;
		return b;
	}

	void push_node(int l)
	{
		lazy += l;
		v.first += l;
	}

	void push_children()
	{
		int mid = (l + r) / 2;
		if (!lc)
		{
			lc = new Node(l, mid);
			rc = new Node(mid + 1, r);
		}
		lc->push_node(lazy);
		rc->push_node(lazy);
		lazy = 0;
	}

	void add(int ql, int qr, int a)
	{
		if (r < ql || l > qr) return;
		if (l>=ql&&r<=qr)
		{
			return push_node(a);
		}
		push_children();
		lc->add(ql, qr, a);
		rc->add(ql, qr, a);
		v = merge(lc->v, rc->v);
	}
};

signed main()
{
	fast();

	int c, r, n;
	cin >> c >> r >> n;

	vector<tuple<int, int, int, int>> events;
	rep(i, n)
	{
		int x1, x2, y1, y2;
		cin >> x1 >> x2 >> y1 >> y2;
		events.emplace_back(y1, 1, x1, x2);
		events.emplace_back(y2, -1, x1, x2);
	}
	
	sort(all(events));
	Node* root = new Node(0, c-1);
	int lasty = 0;
	int ans = 0;
	repe(e, events)
	{
		int y, p, l, r;
		tie(y, p, l, r) = e;
		ans += (root->v.first == 0 ? c-root->v.second : c) * (y-lasty);
		root->add(l, r-1, p);
		lasty = y;
	}
	cout << r*c-ans;
	
	return 0;
}
