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

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

int memo[1010][1010];
int choice[1010][1010];
int best(int i, int j, string& a, string& b)
{
	int& v = memo[i][j];
	if (v != -1) return v;

	if (i == sz(a) && j == sz(b)) return 0;

	int ret = inf;
	bool both = (i < sz(a) && j < sz(b) && a[i] == b[j]);
	if (both)
	{
		ret = 1+best(i + 1, j + 1, a, b);
		choice[i][j] = 0;
	}
	if (i<sz(a))
	{
		int v = 1 + best(i + 1, j, a, b);
		if (v < ret)
		{
			ret = v;
			choice[i][j] = 1;
		}
	}
	if (j<sz(b))
	{
		int v = 1 + best(i, j + 1, a, b);
		if (v < ret)
		{
			ret = v;
			choice[i][j] = 2;
		}

	}
	

	return v = ret;
}

signed main()
{
	fast();

	string a, b;
	getline(cin, a);
	getline(cin, b);

	memset(memo, -1, sizeof(memo));
	best(0, 0, a, b);
	//cout << best(0, 0, a, b);
	p2 state = p2(0, 0);
	string ans = "";
	while (state!=p2(sz(a),sz(b)))
	{
		if (choice[state.first][state.second]==0)
		{
			ans += a[state.first];
			state.first++;
			state.second++;
		}
		else if (choice[state.first][state.second]==1)
		{
			ans += a[state.first];
			state.first++;
		}
		else
		{
			ans += b[state.second];
			state.second++;
		}
	}
	cout << ans;

	return 0;
}
