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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

vi isvowel(256);
signed main()
{
    fast();
	isvowel['a'] = 1;
	isvowel['o'] = 1;
	isvowel['e'] = 1;
	isvowel['i'] = 1;
	isvowel['y'] = 1;
	isvowel['u'] = 1;

	string line;
	while (getline(cin,line))
	{
		stringstream in(line);
		string w;
		while (in >> w)
		{


			string ans1 = "";
			string ans2 = "";
			string pref = "";
			bool sw = 0;
			repe(c, w)
			{
				if (isvowel[c])
				{
					sw = 1;
				}
				if (sw)
				{
					ans2 += c;
					continue;
				}

				ans1 += c;
			}
			if (ans1.empty())
			{
				ans2 += "yay";
			}
			else
			{
				ans2 = ans2 + ans1 + "ay";
			}
			cout << ans2 << " ";
		}
		cout << "\n";
	}

    return 0;
}
