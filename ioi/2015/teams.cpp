#include "teams.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll linf = ll(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct node
{
	int lc=-1, rc=-1;
	int sum = 0;
	node(int lc, int rc, int s) : lc(lc), rc(rc), sum(s) {}
	node() {}
};
int psc = 0;
node pnodes[int(2e7)];

int build(int l, int r)
{
	if (l==r)
	{
		return psc++;
	}
	else
	{
		int mid = (l + r) / 2;
		int ind = psc++;
		pnodes[ind].lc = build(l, mid);
		pnodes[ind].rc = build(mid + 1, r);
		return ind;
	}
}

int update(int x, int l, int r, int i, int s)
{
	if (l==r)
	{
		int ind = psc++;
		pnodes[ind].sum = pnodes[x].sum + s;
		return ind;
	}
	else
	{
		int mid = (l + r) / 2;
		int ind = psc++;
		pnodes[ind].lc = pnodes[x].lc;
		pnodes[ind].rc = pnodes[x].rc;
		if (i <= mid) pnodes[ind].lc = update(pnodes[x].lc, l, mid, i, s);
		else pnodes[ind].rc = update(pnodes[x].rc, mid + 1, r, i, s);
		pnodes[ind].sum = pnodes[pnodes[ind].lc].sum + pnodes[pnodes[ind].rc].sum;
		return ind;
	}
}

int query(int x, int l, int r, int ql, int qr)
{
	if (l > qr || r < ql) return 0;
	if (l >= ql && r <= qr) return pnodes[x].sum;
	int mid = (l + r) / 2;
	return query(pnodes[x].lc, l, mid, ql, qr) + query(pnodes[x].rc, mid + 1, r, ql, qr);
}

int n;
typedef pair<double, int> pt;
vector<p2> pts;

int roots[int(5e5)];

void init(int N, int A[], int B[])
{
	n = N;
	vi a(n);
	vi b(n);
	rep(i, N) a[i] = A[i], b[i] = B[i];

	rep(i, n)
	{
		pts.emplace_back(a[i], b[i]);
	}
	sort(all(pts), [](p2 a, p2 b)
		{
			return a.second < b.second;
		});
	int root = build(0, n - 1);
	rep(i, n)
	{
		root = roots[i] = update(root, 0, n - 1, pts[i].first, 1);
	}
}

int rectangle_sum(int xlo, int xhi, int yhi)
{
	return query(roots[yhi], 0, n - 1, xlo, xhi);
}

struct tnode
{
	p2 corner;
	int value, sum=0, prio, cnt=1;
	tnode *l=0, *r=0;
	tnode(p2 corner, int value) : corner(corner), prio(rand()), value(value) {}
	tnode() {}
};
int node_cnt = 0;
tnode nodes[int(4e5)];

typedef tnode* pnode;
int get_sum(pnode x) { return x ? x->sum : 0; }
int get_cnt(pnode x) { return x ? x->cnt : 0; }
void pull(pnode x)
{
	if (!x) return;
	x->sum = get_sum(x->l) + get_sum(x->r) + x->value;
	x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1;
}

void split(pnode x, pnode& l, pnode& r, int s)
{
	if (!x) return void(l = r = 0);
	if (x->corner.first > s)
		split(x->l, l, x->l, s), r = x;
	else
		split(x->r, x->r, r, s), l = x;
	pull(x);
}

void merge(pnode& x, pnode l, pnode r)
{
	if (!l || !r)
		x = l ? l : r;
	else if (l->prio < r->prio)
		merge(r->l, l, r->l), x = r;
	else
		merge(l->r, l->r, r), x = l;
	pull(x);
}

p2 get_corner(pnode x, int i, int add = 0)
{
	int node_i = add + get_cnt(x->l);
	if (node_i == i) return x->corner;
	if (node_i > i) return get_corner(x->l, i, add);
	return get_corner(x->r, i, add + get_cnt(x->l) + 1);
}

int sum(pnode& root, int xhi, int yhi)
{
	int prev = -1;
	int taken = 0;
	int lo = -1;
	int hi = get_cnt(root);
	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;
		if (get_corner(root, mid).second <= yhi)
		{
			hi = mid;
		}
		else lo = mid;
	}


	int s = 0;
	if (root)
	{
		pnode l, r;
		int lo = -2;
		if (hi) lo = get_corner(root, hi - 1).first;
		split(root, l, r, lo);
		if (r) s = r->sum;
		merge(root, l, r);
	}
	

	if (hi > 0 && get_cnt(root))
	{
		s += rectangle_sum(0, get_corner(root, hi-1).first, yhi);
		
	}
	return rectangle_sum(0, xhi, yhi) - s;
}

const int inf = int(2e9);
p2 invalid = p2(-inf, -inf);
p2 lower_bound(pnode root, int x)
{
	if (!root) return invalid;
	if (root->corner.first >= x)
	{
		p2 left_result = lower_bound(root->l, x);
		if (left_result != invalid) return left_result;
		else return root->corner;
	}
	else
	{
		return lower_bound(root->r, x);
	}
}

p2 rev_bound(pnode root, int x)
{
	if (!root) return invalid;
	p2 result = invalid;

	if (root->corner.first <= x) {
		result = root->corner;
		p2 right_result = rev_bound(root->r, x);
		if (right_result != invalid) result = right_result;
	}
	else result = rev_bound(root->l, x);

	return result;
}

void del(pnode x)
{
	if (!x) return;
	del(x->l);
	del(x->r);
	delete x;
}

int can(int m, int K[]) {
	int t = 0;
	int t2 = 0;
	node_cnt = 0;
	vi k(m);
	rep(i, m) k[i] = K[i];

	sort(all(k));

	pnode hull = 0;
	auto insert = [&](p2 new_corner)
	{
		p2 lo = lower_bound(hull, new_corner.first);
		if ((new_corner.first <= lo.first && new_corner.second <= lo.second))
		{
			// dominated
		}
		else
		{
			while (1)
			{
				p2 p = rev_bound(hull, new_corner.first);
				if (p == invalid) break;
				assert(p.first <= new_corner.first);
				if (p.second <= new_corner.second)
				{
					pnode l, mid, r;
					split(hull, l, r, p.first);
					split(hull, l, mid, p.first - 1);
					merge(hull, l, r);
				}
				else break;
			}
			p2 lo = rev_bound(hull, new_corner.first);

			int s = rectangle_sum((lo.first!=-inf)?lo.first+1:0, new_corner.first, new_corner.second);
			pnode new_node = &nodes[node_cnt++];
			new_node->cnt = 1;
			new_node->corner = new_corner;
			new_node->value = s;
			new_node->sum = 0;
			new_node->l = 0;
			new_node->r = 0;
			pnode l, r;
			split(hull, l, r, new_corner.first);
			merge(hull, l, new_node);
			merge(hull, hull, r);
		}
	};
	int lo = 0;
	rep(i, m)
	{

		lo = lower_bound(pts.begin() + lo, pts.end(), p2(0, k[i]), [](p2 a, p2 b) {
			return a.second < b.second;
			}) - pts.begin();
		if (lo) insert(p2(k[i], lo-1));
		if (sum(hull, k[i], n-1)<k[i])
		{
			return 0;
		}
		int lob = lo-1;
		int hib = n;
		while (lob+1<hib)
		{
			int mid = (lob + hib) / 2;
			if (sum(hull, k[i], mid) < k[i])
			{
				lob = mid;
			}
			else hib = mid;
		}
		p2 new_corner = p2(k[i], hib);
		insert(new_corner);
	}

	return 1;
}
