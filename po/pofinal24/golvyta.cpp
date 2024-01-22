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



signed main()
{
	fast();

	int k;
	cin >> k;
	string s;
	cin >> s;
	int r, c;
	cin >> r >> c;

	vi deltax;
	vi deltay;
	repe(c, s)
	{
		if (c == '>') deltax.push_back(1);
		if (c == '<') deltax.push_back(-1);
		if (c == 'v') deltay.push_back(1);
		if (c == '^') deltay.push_back(-1);
	}

	auto eval = [](vi delta, int size)
	{
		int p = 0;
		repe(v, delta)
		{
			p += v;
			p = max(0LL, p);
			p = min(size, p);
		}
		return p;
	};

	auto solve = [&](vi delta, int t)
	{
		int lo = -1;
		int hi = int(5e5);
		while (lo + 1 < hi)
		{
			int mid = (lo + hi) / 2;
			int p = eval(delta, mid);
			if (p >= t) hi = mid;
			else lo = mid;
		}
		if (eval(delta, hi) == t) return hi;
		return -1LL;
	};
	int x = solve(deltax, c);
	int y = solve(deltay, r);
	if (x == -1 || y == -1) cout << "-1";
	else cout << (x + 1) * (y + 1);
	cout << "\n";

	return 0;
}
