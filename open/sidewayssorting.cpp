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

	int r, c;
	while (cin >> r >> c && r)
	{
		vector<string> words(r);
		rep(i, r) cin >> words[i];
		vi perm(c);
		rep(i, c) perm[i] = i;
		stable_sort(all(perm), [&](int a, int b)
			{
				rep(i, r)
				{
					if (tolower(words[i][a]) < tolower(words[i][b])) return true;
					if (tolower(words[i][a]) > tolower(words[i][b])) return false;
				}
				return a < b;
			});
		vector<string> ans;
		rep(i, r)
		{
			string row = "";
			repe(c, perm)
			{
				row += words[i][c];
			}
			ans.push_back(row);
		}
		repe(w, ans) cout << w << "\n";
		cout << "\n";
	}



	return 0;
}
