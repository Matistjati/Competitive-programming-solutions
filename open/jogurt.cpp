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

void dfs(int level, int index, vvi& tree)
{
	if (level == sz(tree)) return;
	cout << tree[level][index] << " ";
	dfs(level + 1, index * 2, tree);
	dfs(level + 1, index * 2+1, tree);
}

signed main()
{
	fast();

	int n;
	cin >> n;
	n--;
	vvi tree;
	tree.push_back({ 1 });
	// start with valid tree
	// duplicate it, left *= 2, right = right*2+1
	// connect with 1 as root
	// swap bottom rows
	rep(i, n)
	{
		vvi nexttree;
		nexttree.push_back({ 1 });
		vvi left(tree);
		vvi right(tree);
		repe(a, left) repe(v, a) v *= 2;
		repe(a, right) repe(v, a) v = v*2+1;
		rep(j, sz(left))
		{
			vi a = left[j];
			vi b = right[j];
			if (j + 1 == sz(left)) swap(a, b);
			nexttree.push_back({});
			repe(v, a) nexttree[j + 1].push_back(v);
			repe(v, b) nexttree[j + 1].push_back(v);
		}
		tree = nexttree;
	}
	dfs(0, 0, tree);

	return 0;
}
