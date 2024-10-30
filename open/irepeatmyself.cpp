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

	string line;
	getline(cin, line);
	int t = stoi(line);
	while (t--)
	{
		getline(cin, line);
		repp(i, 1, sz(line)+1)
		{
			string c = line;
			string pref = line.substr(0, i);
			
			while (sz(c))
			{
				int ind = c.find(pref);
				if (ind != 0)
				{
					if (pref.find(c)==0)
					{
						c = "";
					}
					break;
				}
				rep(i, sz(pref)) c.erase(c.begin());
			}
			if (c.empty())
			{
				cout << i << "\n";
				break;
			}
		}
	}

	return 0;
}
