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

#define _LOCAL _MSC_VER
#if _LOCAL > 0
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

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]

int get(p2 a, int ind)
{
	return (ind ? a.second : a.first);
}

p2 dp(int u, vector<p2>& gatestate, vi& isleaf)
{
	if (isleaf[u])
	{
		if (gatestate[u].first) return p2(inf, 0);
		return p2(0, inf);
	}

	p2 l = dp(u * 2, gatestate, isleaf);
	p2 r = dp(u * 2 + 1, gatestate, isleaf);

	p2 ret = { inf,inf };
	vi ops = { 0,1 }; // 0 = or
	if (gatestate[u].first == 1) swap(ops[0], ops[1]);
	rep(i, gatestate[u].second)
	{
		int op = ops[i];
		rep(j, 2)
		{
			rep(k, 2)
			{
				int res;
				if (op == 0) res = j | k;
				else res = j & k;
				int cost = i + get(l, j) + get(r, k);

				if (res == 0) ret.first = min(ret.first, cost);
				if (res == 1) ret.second = min(ret.second, cost);
			}
		}
	}
	return ret;
}

signed main()
{
	fast();

	int t;
	cin >> t;
	int c = 1;
	while (t--)
	{
		int n, v;
		cin >> n >> v;

		vector<p2> gatestate(n + 1);
		vi isleaf(n + 1);
		rep(i, (n - 1) / 2)
		{
			cin >> gatestate[i + 1].first >> gatestate[i + 1].second;
			gatestate[i + 1].second++;
		}
		rep(i, (n + 1) / 2)
		{
			isleaf[1 + i + (n - 1) / 2] = 1;
			cin >> gatestate[1 + i + (n - 1) / 2].first;
		}
		p2 res = dp(1, gatestate, isleaf);
		cout << "Case #" << c++ << ": ";
		if (v == 0) cout << (res.first < inf ? to_string(res.first) : "IMPOSSIBLE");
		else cout << (res.second < inf ? to_string(res.second) : "IMPOSSIBLE");
		cout << "\n";
	}

	return 0;
}