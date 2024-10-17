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

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

signed main()
{
	fast();

	int n;
    string temp;

	while (getline(cin,temp))
	{
        n = stoi(temp);
        if (!n) break;
		map<string, vector<string>> whomst;
		rep(i, n)
		{
            string line;
            getline(cin, line);
            vector<string> tokens = split(line, " ");
            repp(i, 1, sz(tokens))
            {
                whomst[tokens[i]].push_back(tokens[0]);
            }
            
		}
        repe(who, whomst)
        {
            cout << who.first << " ";
            sort(all(who.second));
            repe(p, who.second) cout << p << " ";
            cout << "\n";
        }
        cout << "\n";
	}

	return 0;
}
