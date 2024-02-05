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

signed main()
{
	fast();

	string s;
	cin >> s;
	reverse(all(s));
	int n = sz(s);
	set<p2> unique;
	int calls = 0;

	vi lcps(n);
	vi q(n);
	vi next(n);

	int ans = 0;
	auto solve = [&](int ind)
	{
		int p = 0;
		rep(k, ind)
		{
			while (p && lcps[q[p - 1]] > lcps[k])
			{
				next[q[--p]] = k;
			}
			q[p++] = k;
		}
		while (p) next[q[--p]] = ind;

		per(k, ind)
		{
			while (p && lcps[q[p - 1]] > lcps[k])
			{
				next[q[--p]] -= k;
			}
			q[p++] = k;
		}
		while (p) next[q[--p]] -= -1;

		rep(k, ind)
		{
			ans = max(ans, lcps[k] * next[k]);
		}
	};

	repp(l, 1, n)
	{
		rep(i, n) lcps[i] = 0;
		int k = l;
		int ind = 0;
		while (k + l < n)
		{
			int u = 0;
			int its = 0;
			while (s[k + u] == s[k + l + u] && its < l) u++, its++;

			lcps[ind++] = u;
			k += l;
		}
		solve(ind);

		for (int j = l - 1; j >= 0; j--)
		{
			int k = j;
			int ind2 = 0;
			while (k + l < n)
			{
				if (s[k] == s[k + l])
					lcps[ind2] = min(lcps[ind2] + 1, l);
				else
					lcps[ind2] = 0;
				ind2++;
				k += l;
			}

			k = j;
			int ind3 = 0;
			while (k + l * 2 <= n)
			{
				ind3++;
				k += l;
			}

			solve(ind3);
		}
	}
	cout << ans << "\n";



	return 0;
}