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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
	fast();

	int a, b;
	int n;
	cin >> a >> b >> n;
	int ans = abs(a - b) * 4;
	if (b < a) swap(a, b);
	set<int> nums;
	rep(i, n)
	{
		int u;
		cin >> u;
		nums.insert(u);
	}
	repe(u, nums) ans += 10 * (u > a && u < b);
	cout << ans;
	
	return 0;
}
