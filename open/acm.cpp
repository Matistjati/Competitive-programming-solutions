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

    int solve = 0, penalty = 0;
    int t;
    set<char> solved;
    map<char, int> wa;
    while (cin >> t && t != -1)
    {
        char p;
        string verdict;
        cin >> p >> verdict;
        if (solved.count(p))
        {
            continue;
        }
        if (verdict=="wrong")
        {
            wa[p]++;
        }
        if (verdict=="right")
        {
            penalty += t + 20 * wa[p];
            solved.insert(p);
        }
    }
    cout << sz(solved) << " " << penalty;

    return 0;
}
