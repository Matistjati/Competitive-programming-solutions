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


struct Line {
	ll k, m;
	int eval(int x) { return k * x + m; }
	bool operator<(const Line& o) const { return k < o.k; }
	double isect(const Line& other)
	{
		return (double)(other.m - m) / (k - other.k);
	}
};


signed main()
{
	fast();

	int n, k;
	cin >> n >> k;

	auto add = [&](deque<Line>& cht, int k, int m)
	{
		Line newline = Line({ k,m });
		while (cht.size() > 1 && cht.back().isect(newline) < cht[sz(cht) - 2].isect(newline))
		{
			cht.pop_back();
		}
		cht.push_back(Line({ k,m }));
	};
	auto query = [&](deque<Line>& cht, int x)
	{
		while (cht.size() > 1 && cht[0].eval(x) > cht[1].eval(x))
		{
			cht.pop_front();
		}
		return cht[0].eval(x);
	};

	vi nums(n);
	rep(i, n) cin >> nums[i];
	repp(i, 1, n) nums[i] += nums[i - 1];

	vector<deque<Line>> hulls(k + 1);
	add(hulls[0], 0, 0);
	rep(i, n)
	{
		for (int j = k; j > 0; j--)
		{
			if (hulls[j - 1].empty()) continue;
			int cost = nums[i] * nums[i] + query(hulls[j - 1], nums[i]);
			//cout << "i: " << i << ",j: " << j << ": " << cost << "\n";
			if (i == n - 1 && j == k) cout << cost;
			add(hulls[j], -2 * nums[i], cost + nums[i] * nums[i]);
		}
	}

	return 0;
}
