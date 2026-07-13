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
    cin >> r >> c;

    vector<string> grid(r);

    rep(i, r) cin >> grid[i];

    vector<pair<p2, int>> known;
    rep(i, r) rep(j, c) if (grid[i][j] != '.') known.emplace_back(p2(i, j), grid[i][j] - '0');

    auto dist = [](p2 a, p2 b)
    {
        return abs(a.first - b.first) + abs(a.second - b.second);
    };
    rep(i, r)
    {
        rep(j, c)
        {
            if (grid[i][j] != '.')
            {
                cout << grid[i][j];
            }
            else
            {
                vector<p2> intervals;
                repe(k, known)
                {
                    int d = dist(p2(i, j), k.first);
                    intervals.emplace_back(k.second - d, k.second + d);
                }
                int num_good = 0;
                int isgood = 0;
                rep(v, 10)
                {
                    bool good = 1;
                    repe(inter, intervals)
                    {
                        good &= (v >= inter.first && v <= inter.second);
                    }
                    if (good) num_good++, isgood = v;
                }
                if (num_good == 1)
                {
                    cout << isgood;
                }
                else cout << ".";
            }
        }
        cout << "\n";
    }

    return 0;
}
