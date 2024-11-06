// bruh task. they do not specify j,k,l to be positive integers
// so the statement is incorrect
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
	while (cin >> n && n)
	{
		int canada_ind = -1;
		vector<tuple<int, int, int>> countries;
		int t = 0;
		rep(i, n)
		{
			string name;
			int g, s, b;
			cin >> name >> g >> s >> b;
			if (name == "Canada") canada_ind = i;
			t += g;
			t += s;
			t += b;
			countries.emplace_back(g, s, b);
		}
		if (canada_ind==-1)
		{
			cout << "Canada cannot win." << "\n";
			continue;
		}
		auto getscore = [&](double a, double b, double c, int i)
		{
			double g, s, bb;
			tie(g, s, bb) = countries[i];
			return 1 / pow(t, a) * g + 1 / pow(t, b) * s + 1 / pow(t, c) * bb;
		};
		bool canwin = 0;
		rep(a, 8) rep(b, 8) rep(c, 8)
		{
			double canada = getscore(a, b, c, canada_ind);
			bool wins = 1;
			rep(i, n)
			{
				wins &= canada >= getscore(a, b, c, i);
			}
			canwin |= wins;
		}
		cout << (canwin ? "Canada wins!" : "Canada cannot win.") << "\n";
	}

	return 0;
}
