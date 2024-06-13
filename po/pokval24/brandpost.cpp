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

typedef tuple<int, int, int> p3;
signed main()
{
	fast();

	int r, c, n;
	cin >> c >> r >> n;

	vector<p2> hydrants;
	int ic = 0;
	rep(i, n)
	{
		int a, b;
		cin >> b >> a;
		a--; b--;
		if (p2(a, b) == p2(0, 0))ic = 1;
		hydrants.emplace_back(a, b);
	}

	vvi cost(r, vi(c));
	rep(i, r)
	{
		int t = i + 1;
		int w = 0;
		repe(h, hydrants)
		{
			w += max(0LL, t - abs(i - h.first)-h.second);
		}
		priority_queue<int, vi, greater<int>> activeright;
		sort(all(hydrants), [i](const p2& a, const p2& b)
			{
				return abs(a.first-i) + a.second < abs(b.first-i) + b.second;
			});

		int hindex = 0;
		while (hindex < sz(hydrants) && t >= abs(hydrants[hindex].first - i) + abs(hydrants[hindex].second))
		{
			activeright.push(hydrants[hindex++].second);
		}
		rep(j, c)
		{
			cost[i][j] = w;
			t = i + j + 2;
			while (sz(activeright) && activeright.top() < j + 1) activeright.pop();
			w += sz(activeright) * 2;
			
			while (hindex < sz(hydrants) && (hydrants[hindex].second < j+1|| t >= abs(hydrants[hindex].first - i) + abs(hydrants[hindex].second - j - 1)))
			{
				if (hydrants[hindex].second<j+1)
				{
					hindex++;
					continue;
				}
				w += max(0LL,t - abs(hydrants[hindex].first - i) - abs(hydrants[hindex].second - j - 1));
				activeright.push(hydrants[hindex++].second);
			}
		}
	}

	vvi dp(r, vi(c,inf));
	dp[0][0] = ic;
	rep(i, r)
	{
		rep(j, c)
		{
			if (i != r - 1) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + cost[i + 1][j]);
			if (j != c - 1) dp[i][j+1] = min(dp[i][j+1], dp[i][j] + cost[i][j+1]);
		}
	}
	cout << dp.back().back();
	return 0;
	
}
