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

void solve()
{
	int n, r;
	cin >> n >> r;

	int ans = 0;
	int rem = 0;
	rep(i, n)
	{
		int x;
		cin >> x;
		ans += x / 2*2;
		r -= x / 2;
		if (x%2)
		{
			rem++;
		}
	}
	if (rem % 2)
	{
		r-=(rem+1)/2;
		ans++;
		rem--;
	}
	else
	{
		r -= rem / 2;
	}
	
	while (r&&rem>1)
	{
		ans+=2;
		r--;
		rem-=2;
	
	}
	cout << ans << "\n";
}

signed main()
{
    fast();

	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}

    return 0;
}
