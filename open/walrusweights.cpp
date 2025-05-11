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

    int n;
    cin >> n;

    bitset<2010> bset;
    bset[0] = 1;
    rep(i, n)
    {
        int w;
        cin >> w;
        bset |= bset << w;
    }

    int bestdist = inf;
    rep(i, 2010) if (bset[i] && abs(i - 1000) < bestdist) bestdist = abs(i - 1000);
    int distcnt = 0;
    rep(i, 2010) if (bset[i] && abs(i - 1000) == bestdist) distcnt++;
    if (distcnt==2)
    {
        cout << 1000 + bestdist;
    }
    else rep(i,2010) if (bset[i] && abs(i - 1000) == bestdist) cout << i;

    return 0;
}
