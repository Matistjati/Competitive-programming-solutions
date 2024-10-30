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

	vector<string> grid(5);
	rep(i, 5) cin >> grid[i];
	vector<p2> dirs = { {1,2},{-1,2},{1,-2},{-1,-2},{2,1},{-2,1},{2,-1},{-2,-1} };

	int cnt = 0;
	rep(i, 5)rep(j, 5) if (grid[i][j]=='k')
	{
		cnt++;
		repe(dir, dirs)
		{
			p2 np = p2(i + dir.first, j + dir.second);
			if (np.first < 0 || np.second < 0 || np.first >= 5 || np.second >= 5) continue;
			if (grid[np.first][np.second]=='k')
			{
				cout << "invalid";
				return 0;
			}
		}
	}
	if (cnt==9) cout << "valid";
	else cout << "invalid";

	return 0;
}
