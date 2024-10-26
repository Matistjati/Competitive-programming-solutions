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

int dp[205][205];
string word;
int best(int l, int r)
{
	if (l > r) return 0;
	if (l == r) return 2;
	char c = word[l];

	int& v = dp[l][r];
	if (v != -1) return v;

	int ret = inf;
	int cost = 2;

	ret = min(ret, 2 + best(l + 1, r));
	// c is on top of stack
	repp(i, l+1, r+1)
	{
		if (word[i]==c)
		{
			ret = min(ret, best(l, i-1) + best(i+1,r));
		}
	}

	return v=ret;
}

signed main()
{
	fast();

	string line;
	getline(cin, line);
	int n = stoi(line);
	while (n--)
	{
		getline(cin, word);
		memset(dp, -1, sizeof(dp));

		cout << best(0, sz(word) - 1)+sz(word) << "\n";
	}

	return 0;
}
