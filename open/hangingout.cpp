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

	int l, x;
	cin >> l >> x;
	int c = 0;
	int ans = 0;
	while (x--)
	{
		string a;
		int b;
		cin >> a >> b;
		if (a == "enter")
		{
			if (c + b <= l) c += b;
			else ans++;
		}
		else c -= b;
	}
	cout << ans;

	return 0;
}
