#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
//const int inf = int(1e18);

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

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }


#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int maxn = int(1e6);
int n;
vi nums;

signed main()
{
	fast();

	//ifstream in("C:\\Users\\matis\\desktop\\comp_prog\\x64\\debug\\in.txt");
	//cin.rdbuf(in.rdbuf());
	cin >> n;
	nums.resize(n);
	rep(i, n) cin >> nums[i];
	vector<p2> numsorted(n);
	rep(i, n) numsorted[i] = p2(nums[i], i);
	sort(all(numsorted));

	vector<p2> previntervals(n, p2(-1, -1));
	vector<vector<int>> goodintervals(n);

	priority_queue<p2> pq;
	repe(v, numsorted) pq.emplace(-v.first, v.second);
	vector<p2> currintervals;


	while (pq.size()) // invariant: all intervals in currintervals are same size
	{
		int s = -pq.top().first;
		while (pq.size() && -pq.top().first == s)
		{
			currintervals.emplace_back(pq.top().second, pq.top().second);
			pq.pop();
		}
		sort(all(currintervals));

		while (currintervals.size())
		{
			vector<p2> nextintervals;

			for (int j = sz(currintervals) - 1; j >= 0; j--)
			{
				p2 val = currintervals[j];
				previntervals[val.first] = { s, val.second };
				goodintervals[val.first].push_back(val.second);

				if (val.second == n - 1) continue;
				if (previntervals[val.second + 1].first != s) continue;

				while (pq.size() && -pq.top().first == s + 1 && pq.top().second >= val.first)
				{
					nextintervals.emplace_back(pq.top().second, pq.top().second);
					pq.pop();
				}

				nextintervals.emplace_back(val.first, previntervals[val.second + 1].second);
			}

			while (pq.size() && -pq.top().first == s + 1)
			{
				nextintervals.emplace_back(pq.top().second, pq.top().second);
				pq.pop();
			}

			reverse(all(nextintervals));
			currintervals = nextintervals;
			s++;
		}
	}

	vi dp(n + 1, int(2e9));
	dp[0] = 0;
	rep(i, n)
	{
		repe(g, goodintervals[i])
		{
			dp[g + 1] = min(dp[g + 1], 1 + dp[i]);
		}
	}

	cout << dp.back();


	return 0;
}
