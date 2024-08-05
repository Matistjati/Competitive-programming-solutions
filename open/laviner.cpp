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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


p2 dfs2(int u, int p, int compsize, vvi& edges)
{
    p2 ret = p2(0, 1);

    repe(e, edges[u])
    {
        if (e == p) continue;
        p2 r = dfs2(e, u, compsize, edges);
        ret = p2(ret.first + r.first, ret.second + r.second);
    }

    if (ret.second >= compsize) ret.first++, ret.second = 0;
    return ret;
}

signed main()
{
    fast();

    int n, k;
    cin >> n >> k;
    vvi edges(n);
    rep(i, n-1)
    {
        int u;
        cin >> u;
        u--;
        edges[u].push_back(i+1);
        edges[i+1].push_back(u);
    }

    int lo = -1;
    int hi = n + 1;
    while (lo+1<hi)
    {
        int mid = (lo + hi) / 2;
        if (dfs2(0, 0, mid, edges).first > k) lo = mid;
        else hi = mid;
    }
    cout << lo;

    return 0;
}
