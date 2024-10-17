#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
	fast();

	int n;
	cin >> n;

	vi time(int(1e5));
	rep(i, n)
	{
		int m;
		cin >> m;
		rep(i, m)
		{
			int l, r;
			cin >> l >> r;
			repp(j, l, r + 1) time[j]++;
		}
	}

	int ans = *max_element(all(time));
	int ans2 = 0;
	rep(i, sz(time)) ans2 += time[i] == ans;
	cout << ans << " " << ans2;

	return 0;
}
