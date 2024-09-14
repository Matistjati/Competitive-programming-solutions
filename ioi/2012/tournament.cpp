#if _LOCAL
#include "tournament.h"
#endif

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int inf = int(1e9);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct fenwick
{
	vi tree;
	fenwick(int n) : tree(n+1) {}

	void update(int i, int v)
	{
		for (i++; i < sz(tree); i += i & -i) tree[i] += v;
	}

	int query(int r)
	{
		int ret = 0;
		for (r++; r > 0; r -= r & -r) ret += tree[r];
		return ret;
	}

	int query(int l, int r) // [l,r]
	{
		if (l) l = query(l - 1);
		return query(r) - l;
	}
};

vi color;
p2 best=p2(-1, inf);
pair<int, p2> invalid = { -1,p2(-1,-1) };
pair<int,p2> dfs(int u, vvi& children)
{
	if (sz(children[u]) == 0)
	{
		if (best.first == -1) best = p2(0, u);
		if (best.first == 0 && u < best.second) best = p2(0, u);
		return { color[u], p2(0, u) };
	}

	pair<int, p2> ret = { 0, p2(-1, -1) };
	rep(i, sz(children[u]))
	{
		pair<int, p2> r = dfs(children[u][i], children);
		if (r == invalid) ret = invalid;
		if (ret == invalid) continue;
		if (r.first)
		{
			if (i != 0) ret = invalid;
			else ret = { 1, p2(r.second.first + 1,r.second.second) };
		}
		else if (r.second.first+1 > ret.second.first || (r.second.first+1==ret.second.first && r.second.second<ret.second.second))
		{
			ret = { ret.first, p2(r.second.first + 1,r.second.second) };
		}
	}
	if (ret == invalid) return ret;
	if (ret.second.first > best.first)
	{
		best = ret.second;
	}
	if (ret.second.first == best.first && ret.second.second < best.second)
	{
		best = ret.second;
	}
	return ret;
}

int GetBestPosition(int n, int c, int r, int *K, int *S, int *E)
{
	fenwick tree(n);
	rep(i, n) tree.update(i, 1);
	vi s(c);
	vi e(c);
	vi k(n-1);
	rep(i, n - 1) k[i] = K[i];
	rep(i, c) s[i] = S[i];
	rep(i, c) e[i] = E[i];

	vi par(n+c);
	vi left_endpoint(n + c, inf);
	vi nodes(n);
	rep(i, n) nodes[i] = i;
	rep(i, n) left_endpoint[i] = i;

	rep(i, c)
	{
		int new_node = i + n;
		int l = e[i] - s[i] + 1;
		int u = -1;
		rep(j, l)
		{
			int lo = -1;
			int hi = n;
			while (lo+1<hi)
			{
				int mid = (lo + hi) / 2;
				if (tree.query(mid) >= s[i]+1)
				{
					hi = mid;
				}
				else lo = mid;
			}
			int v = nodes[hi];
			tree.update(hi, -1);
			par[v] = new_node;
			left_endpoint[par[v]] = min(left_endpoint[par[v]], left_endpoint[v]);
			u = hi;
		}
		assert(u != -1);
		nodes[u] = new_node;
		tree.update(u, 1);
	}

	vvi children(n+c);
	rep(i, sz(par) - 1) children[par[i]].push_back(i);
	rep(i, sz(children)) sort(all(children[i]), [&](int i, int j)
		{
			return left_endpoint[i] < left_endpoint[j];
		});
	color.resize(n);
	rep(i, n - 1) color[i + 1] = k[i] > r;
	dfs(sz(par)-1, children);
	return best.second;
}
