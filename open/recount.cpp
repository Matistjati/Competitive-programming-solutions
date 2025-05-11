#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

signed main()
{
    fast();

    string line;
    map<string, int> occs;
    while (getline(cin,line))
    {
        if (line == "***") break;
        occs[line]++;
    }

    int m = 0;
    repe(o, occs) m = max(m, o.second);
    int mcnt = 0;
    repe(o, occs) if (o.second == m) mcnt++;
    if (mcnt > 1)
    {
        cout << "Runoff!";
    }
    else repe(o, occs) if (o.second == m) cout << o.first;

    return 0;
}
