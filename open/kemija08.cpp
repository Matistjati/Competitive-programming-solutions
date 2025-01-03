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

	string x;
	getline(cin, x);

	string ans;

	auto isvowel = [](char c)
	{
		return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
	};

	repe(c, x)
	{
		if (sz(ans)>1&&isvowel(c))
		{
			if (ans.back() == 'p' && ans[sz(ans) - 2] == c)
			{
				ans.pop_back();
				ans.push_back('$');
				continue;
			}
		}
		ans.push_back(c);
	}
	repe(c, ans) if (c != '$') cout << c;

	return 0;
}