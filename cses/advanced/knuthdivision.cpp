//#pragma GCC optimize("Ofast,inline,unroll-loops")
//#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")//,tune=native")

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

	int n;
	cin >> n;
	vi nums(n);
	rep(i, n) cin >> nums[i];
	repp(i, 1, n) nums[i] += nums[i - 1];
	n++;
	nums.insert(nums.begin(), 0);
	vector<vector<p2>> dp(n, vector<p2>(n, p2(inf, -1)));
	rep(i, n) dp[i][i] = p2(0, i);

	repp(k, 1, n)
	{
		repp(l, 1, n)
		{
			int r = l + k;
			if (r >= n) continue;

			int left = dp[l][r - 1].second;
			int right = dp[l + 1][r].second;

			repp(p, left, min(r, right + 1))
			{
				int v = nums[r] - nums[l - 1] + dp[l][p].first + dp[p + 1][r].first;
				if (v < dp[l][r].first)
				{
					dp[l][r] = p2(v, p);
				}
			}
		}
	}
	cout << dp[1][n - 1].first;

	return 0;
}
