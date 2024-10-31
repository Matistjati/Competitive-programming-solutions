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

	string s;
	cin >> s;
	reverse(all(s));

	__int128_t start = 1;
	__int128_t ans = inf;
	while (start< __int128_t(1e17))
	{
		__int128_t k = start;
		bool good = 1;
		repe(c, s)
		{
			if (c=='O')
			{
				if ((k - 1) % 3 != 0)
				{
					good = 0;
					break;
				}
				k = (k - 1) / 3;
				if (k%2==0)
				{
					good = 0;
					break;
				}
			}
			else
			{
				k *= 2;
			}
			if ((k&(k-1))==0)
			{
				good = 0;
				break;
			}
		}
		if (good)
		{
			ans = k;
			break;
		}
		start *= 2;
	}
	if (ans!=inf) cout << (ll)ans;
	else cout << "INVALID";

	return 0;
}
