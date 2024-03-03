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
#define assert(x) if (!(x)) __debugbreak()
#endif

struct query
{
	int l, r, lo, hi;
	int a, c, d;
	bool operator<(const query& other) const {
		return lo < other.lo;
	}
};

struct Tree {
	typedef p2 T;
	static constexpr T unit = p2(inf, -1);
	T f(T a, T b) { if (a.first < b.first) return a; return b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

signed main()
{
	fast();

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vi nums(n);
		rep(i, n) cin >> nums[i];

		vector<p2> numsorted;
		rep(i, n) numsorted.emplace_back(nums[i], i);
		sort(all(numsorted));

		int m = -inf;
		int mind = -1;
		vector<p2> sufmax(n);
		for (int i = n - 1; i >= 0; i--)
		{
			sufmax[i] = { m,mind };
			if (nums[i] > m)
			{
				m = nums[i];
				mind = i;
			}
		}
		vi prefmin(n);
		m = inf;
		vector<query> queries;
		rep(i, n)
		{
			m = min(m, nums[i]);
			prefmin[i] = m;
		}

		rep(i, n)
		{
			int v = nums[i];
			if (sufmax[i].first <= v) continue;

			int l = -1;
			int r = i;
			while (l + 1 < r)
			{
				int mid = (l + r) / 2;
				if (prefmin[mid] < v)
				{
					r = mid;
				}
				else l = mid;
			}

			if (r != -1)
			{
				queries.emplace_back(query({ r + 1,i,v, sufmax[i].first,r + 1,i + 1,sufmax[i].second + 1 }));
			}
		}

		sort(all(queries));
		reverse(all(queries));
		Tree tree(n);
		int p = n - 1;
		repe(q, queries)
		{
			while (p > 0 && p >= q.lo)
			{
				tree.update(numsorted[p].second, p2(numsorted[p].first, numsorted[p].second));
				p--;
			}
			if (tree.query(q.l, q.r).first < q.hi)
			{
				cout << q.a << " " << tree.query(q.l, q.r).second + 1 << " " << q.c << " " << q.d << "\n";
				goto done;
			}
		}

		cout << "Ekkert mynstur!\n";
	done:;
	}

	return 0;
}
