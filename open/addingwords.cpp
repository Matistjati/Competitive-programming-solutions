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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    map<string, int> wordtovalue;
    map<int, string> valuetoword;
    
    string command;
    while (cin >> command)
    {
        if (command == "def")
        {
            string name;
            int value;
            cin >> name >> value;
            if (wordtovalue.count(name)) valuetoword.erase(wordtovalue[name]);
            wordtovalue[name] = value;
            valuetoword[value] = name;
        }
        if (command == "calc")
        {
            string beg;
            cin >> beg;
            vector<pair<string, char>> exp;
            string name;
            char op;
            while (cin >> op)
            {
                if (op == '=') break;
                cin >> name;
                exp.emplace_back(name, op);
            }

            bool good = 1;
            good &= wordtovalue.count(beg);
            repe(u, exp) good &= wordtovalue.count(u.first);
            int v = -inf;
            if (good)
            {
                v = wordtovalue[beg];
                repe(u, exp)
                {
                    if (u.second=='+')
                    {
                        v += wordtovalue[u.first];
                    }
                    else v -= wordtovalue[u.first];
                }
            }
            string res = "unknown";
            if (valuetoword.count(v))
            {
                res = valuetoword[v];
            }
            cout << beg << " ";
            repe(u, exp) cout << u.second << " " << u.first << " ";
            cout << "= " << res << "\n";
        }
        if (command == "clear")
        {
            wordtovalue.clear();
            valuetoword.clear();
        }
    }

    return 0;
}
