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

	set<string> seen;
	map<char, int> occ;

	occ['P'] = 13;
	occ['K'] = 13;
	occ['H'] = 13;
	occ['T'] = 13;
	string x;
	cin >> x;
	for (int i = 0; i < sz(x); i += 3)
	{
		string sub = x.substr(i, 3);
		if (seen.find(sub)!=seen.end())
		{
			cout << "GRESKA";
			return 0;
		}
		seen.insert(sub);
		occ[sub[0]]--;

	}
	cout << occ['P'] << " " << occ['K'] << " " << occ['H'] << " " << occ['T'];

	return 0;
}
