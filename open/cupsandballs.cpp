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

	vi cups = { 0,1,0 };
	int g, n;
	cin >> g >> n;
	g--;
	rep(i, n)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		swap(cups[a], cups[b]);
	}
	if (cups[g])
	{
		rep(i, 3) if (i != g) cout << i + 1 << " ";
	}
	else
	{
		cout << g + 1 << " ";
		rep(i, 3) if (cups[i]) cout << i + 1;
	}

	return 0;
}
