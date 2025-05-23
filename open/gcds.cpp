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

	set<int> waiting;
	set<int> ans;
	rep(i, n)
	{
		int v;
		cin >> v;
		set<int> next;
		repe(w, waiting)
		{
			int g = gcd(w, v);
			ans.insert(g);
			next.insert(g);
		}
		next.insert(v);
		ans.insert(v);
		waiting = next;
	}

	cout << sz(ans);

	return 0;
}
