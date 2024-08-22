// partial: 60p
#include "meetings.h"

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

typedef vector<ll> vll;

struct node
{
	ll best=0, l, r;
	ll split;
	node *lc=0, *rc=0;
	node(ll l, ll r) : l(l), r(r) {}
};

vll h;
int n;
node* build_tree(int l, int r)
{
	if (l > r) return 0;
	if (r < l) return 0;
	node* ret = new node(l, r);
	if (l==r)
	{
		ret->best = h[l];
		ret->split = l;
		return ret;
	}
	ll largest = 0;
	repp(i, l, r + 1) largest = max(largest, h[i]);

	vll lindex;
	repp(i, l, r + 1) if (h[i] == largest) lindex.push_back(i);
	int split = lindex[sz(lindex) / 2];
	ret->split = split;

	ret->lc = build_tree(l, split - 1);
	ret->rc = build_tree(split + 1, r);

	ll lcost = (r - (split + 1) + 2) * largest;
	if (ret->lc) lcost += ret->lc->best;
	ll rcost = ((split - 1) - l + 2) * largest;
	if (ret->rc) rcost += ret->rc->best;
	ret->best = min(lcost, rcost);

	return ret;
}

ll query(node* x, int ql, int qr)
{
	if (!x) return 0;
	if (x->l >= ql && x->r <= qr)
	{
		return x->best;
	}
	if (x->l > qr || x->r < ql) return 0;
	if (qr < x->split) return query(x->lc, ql, qr);
	if (ql > x->split) return query(x->rc, ql, qr);
	ll a = max(0LL, x->split - 1 - ql + 2) * h[x->split] + query(x->rc, x->split+1, qr);
	ll b = max(0LL, qr - x->split - 1 + 2) * h[x->split] + query(x->lc, ql, x->split-1);
	return min(a, b);
}


vll minimum_costs(vi H, std::vector<int> L, std::vector<int> R)
{
	h = vll(H.begin(), H.end());
	n = sz(h);
	node* root = build_tree(0, n - 1);
	int q = sz(L);
	vll ret(q);
	rep(qu, q)
	{
		int l = L[qu];
		int r = R[qu];
		ret[qu] = query(root, l, r);
	}
	return ret;
}
