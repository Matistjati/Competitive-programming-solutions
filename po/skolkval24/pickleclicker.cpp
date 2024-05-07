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

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();

	int n, t;
	cin >> n >> t;
	vector<p2> buildings(n);
	rep(i, n) cin >> buildings[i].first >> buildings[i].second;


	unordered_map<int, int> dp;
	// dp[production]=max pickles
	dp[buildings[0].first] = 0;

	int ans = 0;
	while (sz(dp))
	{
		ans++;
		unordered_map<int, int> nextdp;
		repe(s, dp)
		{
			if (s.first + s.second >= t)
			{
				cout << ans;
				return 0;
			}
			nextdp[s.first] = max(nextdp[s.first], s.first + s.second);
			rep(j, n)
			{
				if (s.first + s.second < buildings[j].second) continue;
				int newp = s.first + buildings[j].first;
				nextdp[newp] = max(nextdp[newp], s.first + s.second - buildings[j].second);
			}
		}
		dp = nextdp;
	}

	return 0;
}