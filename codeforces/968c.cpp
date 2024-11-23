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

void solve()
{
	int n;
	string s;
	cin >> n >> s;

	map<char, int> occ;
	repe(c, s) occ[c]++;

	priority_queue<pair<int, char>> chars;
	repe(o, occ) chars.emplace(o.second, o.first);
	string ans;

	while (sz(chars))
	{
		int p;
		char c;
		tie(p, c) = chars.top();
		chars.pop();
		if (sz(ans)&& sz(chars)&&c==ans.back())
		{
			int pc;
			char cc;
			tie(pc, cc) = chars.top();
			chars.pop();
			ans += cc;
			pc--;
			if (pc) chars.emplace(pc, cc);

			chars.emplace(p, c);
		}
		else
		{
			ans += c;
			p--;
			if (p) chars.emplace(p, c);
		}
	}

	cout << ans << "\n";
}

signed main()
{
	fast();

	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
	
	return 0;
}
