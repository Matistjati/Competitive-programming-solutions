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

int dp[21][1 << 15];
int ansmask;
vector<tuple<int, int, int>> stops;
int dist(p2 a, p2 b) { return abs(a.first - b.first) + abs(a.second - b.second); }
p2 get_pos(int i) { return  p2(get<0>(stops[i]), get<1>(stops[i])); }
int best(int pos, int mask)
{
	p2 p = get_pos(pos);
	if (mask==ansmask)
	{
		return abs(p.first)+abs(p.second);
	}
	int& v = dp[pos][mask];
	if (v != -1) return v;
	int ret = inf;
	rep(i, sz(stops))
	{
		p2 theirs = get_pos(i);
		int b = get<2>(stops[i]);
		if ((mask|b)!=mask)
		{
			ret = min(ret, dist(p, theirs) + best(i, mask | b));
		}
	}
	return v=ret;
}


signed main()
{
	fast();
	memset(dp, -1, sizeof(dp));

	int n;
	cin >> n;
	map<string, int> nameind;
	rep(i, n)
	{
		int r, c;
		string name;
		cin >> r >> c >> name;
		if (nameind.find(name) == nameind.end()) nameind[name] = 1 << sz(nameind);
		stops.emplace_back(r, c, nameind[name]);
	}
	ansmask = (1 << sz(nameind)) - 1;
	stops.emplace_back(0, 0, 0);
	cout << best(sz(stops) - 1, 0);


	return 0;
}
