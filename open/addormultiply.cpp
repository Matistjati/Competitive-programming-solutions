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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define __builtin_clz __lzcnt
#define assert(x) if (!(x)) __debugbreak()
#endif


const int mod = int(1e9 + 7);

struct Tree
{
	vector<vi> tree;
	vector<bool> isplus;

	Tree(int n) : tree(n * 4, vi(1)), isplus(n * 4, 1) {}

	vi merge(vi left, vi right, bool plus)
	{
		if (sz(left) == 0) return right;
		if (sz(right) == 0) return left;
		if (plus)
		{
			if (sz(right)==1)
			{
				if (sz(left) > 2)
				{
					left[1] = (left[1]+left[2])%mod;
					left.pop_back();
				}
				left.push_back(right[0]);
			}
			else if (sz(right)==2)
			{
				left.push_back(right[0]);
				while (sz(left) > 2) left[1] = (left[1]+left.back())%mod, left.pop_back();
				left.push_back(right[1]);
			}
			else if (sz(right) == 3)
			{
				left.push_back(right[0]);
				left.push_back(right[1]);
				while (sz(left) > 2) left[1] = (left[1]+left.back())%mod, left.pop_back();
				left.push_back(right[2]);
			}
			
			assert(sz(left) <= 3);
			return left;
		}
		else
		{
			if (sz(right) == 1)
			{
				left.back() = (left.back()*right[0])%mod;
			}
			else if (sz(right) == 2)
			{
				left.back() = (left.back()*right[0])%mod;
				while (sz(left) > 2) left[1] = (left[1]+left[2])%mod, left.pop_back();
				left.push_back(right[1]);
			}
			else if (sz(right) == 3)
			{
				left.back() = (left.back()*right[0])%mod;
				left.push_back(right[1]);
				while (sz(left) > 2) left[1] = (left[1]+left.back())%mod, left.pop_back();
				left.push_back(right[2]);
			}
			else assert(0);
			
			assert(sz(left) <= 3);
			return left;
		}
	}

	void updateval(int x, int l, int r, int i, int v)
	{
		if (l == r) tree[x] = { v };
		else
		{
			int mid = (l + r) / 2;
			if (i <= mid) updateval(x * 2, l, mid, i, v);
			else updateval(x * 2 + 1, mid + 1, r, i, v);
			tree[x] = merge(tree[x * 2], tree[x * 2 + 1], isplus[x]);
		}
	}

	void updateop(int x, int l, int r, int i, bool plus)
	{
		int mid = (l + r) / 2;
		if (i<=mid&&i+1>mid)
		{
			isplus[x] = plus;
		}
		else
		{
			if (i <= mid) updateop(x * 2, l, mid, i, plus);
			else updateop(x * 2 + 1, mid + 1, r, i, plus);
		}
		
		tree[x] = merge(tree[x * 2], tree[x * 2 + 1], isplus[x]);
	}
};

signed main()
{
	fast();

	int n, q;
	cin >> n >> q;

	string s;
	cin >> s;
	vector<bool> isplus(n - 1);
	Tree normal(n);
	Tree inverse(n);
	vi nums(n);
	rep(i, n)
	{
		nums[i] = s[i * 2] - '0';
		normal.updateval(1, 0, n - 1, i, s[i * 2] - '0');
		inverse.updateval(1, 0, n - 1, i, s[i * 2] - '0');
	}
	rep(i, n-1)
	{
		isplus[i] = s[i * 2 + 1] == '+';
		normal.updateop(1, 0, n - 1, i, s[i * 2+1] == '+');
		inverse.updateop(1, 0, n - 1, i, s[i * 2 + 1] == '*');
	}
	cout << accumulate(all(normal.tree[1]), 0LL)%mod << "\n";
	bool flipped = 0;
	while (q--)
	{
		char t;
		cin >> t;
		if (t=='s')
		{
			int a, b;
			cin >> a >> b;
			a--; b--;
			int av = nums[a];
			int bv = nums[b];
			normal.updateval(1, 0, n - 1, a, bv);
			normal.updateval(1, 0, n - 1, b, av);
			
			inverse.updateval(1, 0, n - 1, a, bv);
			inverse.updateval(1, 0, n - 1, b, av);
			nums[a] = bv;
			nums[b] = av;
		}
		else if (t=='a')
		{
			flipped = !flipped;
		}
		else if (t=='f')
		{
			int a;
			cin >> a;
			a--;
			isplus[a] = !isplus[a];
			normal.updateop(1, 0, n - 1, a, isplus[a]);
			inverse.updateop(1, 0, n - 1, a, !isplus[a]);
		}

		vi res;
		if (flipped) res = inverse.tree[1];
		else res = normal.tree[1];
		cout << accumulate(all(res),0LL)%mod << "\n";
	}
	

	return 0;
}
