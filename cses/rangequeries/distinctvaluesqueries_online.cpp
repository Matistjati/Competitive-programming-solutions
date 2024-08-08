#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define rep(i,n) for(int i = 0; i < n; i++)
typedef pair<int, int> p2;

struct Node
{
	int left = -1, right = -1;
	int sum = 0;

	Node(int l, int r) : left(l), right(r) {}
	Node(int v) : sum(v) {}
	Node() {}
};

const int maxn = int(2e5 + 10);
int roots[maxn];
Node nodes[int(8e6)];
int nodep = 0;
int build(int l, int r)
{
	if (l == r)
	{
		nodes[nodep] = Node(0);
		return nodep++;
	}
	else
	{
		int mid = (l + r) / 2;
		int ret = nodep++;
		nodes[ret] = Node(0);
		nodes[ret].left = build(l, mid);
		nodes[ret].right = build(mid + 1, r);
		return ret;
	}
}

int update(Node& x, int l, int r, int i, int v)
{
	if (l == r)
	{
		nodes[nodep] = Node(v);
		return nodep++;
	}
	else
	{
		int mid = (l + r) / 2;
		int ret = nodep++;

		nodes[ret] = Node(x.left, x.right);
		Node& newnode = nodes[ret];
		if (i <= mid) newnode.left = update(nodes[x.left], l, mid, i, v);
		else newnode.right = update(nodes[x.right], mid + 1, r, i, v);
		newnode.sum = nodes[newnode.left].sum + nodes[newnode.right].sum;
		if (newnode.sum > 3)
		{
			cout << "";
		}
		return ret;
	}
}

int query(Node& x, int l, int r, int ql, int qr)
{
	if (l > qr || r < ql) return 0;
	if (l >= ql && r <= qr) return x.sum;
	int mid = (l + r) / 2;
	return query(nodes[x.left], l, mid, ql, qr) + query(nodes[x.right], mid + 1, r, ql, qr);
}
inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

signed main()
{
	fast();
	int n, q;
	cin >> n >> q;
	int ind = 0;
	roots[ind++] = build(0, n - 1);


	map<int, int> lastocc;
	rep(i, n)
	{
		int v;
		cin >> v;
		Node root = nodes[roots[ind - 1]];
		if (lastocc.find(v) != lastocc.end())
		{
			int index = lastocc[v];
			root = nodes[update(root, 0, n - 1, index, 0)];
		}
		lastocc[v] = i;
		roots[ind++] = update(root, 0, n - 1, i, 1);
	}

	rep(i, q)
	{
		int l, r;
		cin >> l >> r;
		l--;
		Node& root = nodes[roots[r]];
		cout << query(root, 0, n - 1, l, n - 1) << "\n";
	}

	return 0;
}