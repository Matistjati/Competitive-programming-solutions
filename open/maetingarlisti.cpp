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

	int r, c, n;
	cin >> n >> r >> c;
	vector<vector<string>> grid(r, vector<string>(c));
	rep(i, r)
	{
		rep(j, c) cin >> grid[i][j];
	}

	rep(i, r)
	{
		vector<string> row;
		rep(j, c)
		{
			string x;
			cin >> x;
			row.push_back(x);
		}
		cout << (grid[i][0] == row[0] ? "left" : "right") << "\n";
	}

	return 0;
}
