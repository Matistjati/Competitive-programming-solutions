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

    int n;
    cin >> n;
    vvi rows(3, vi(n));
    rep(i, 3) rep(j, n) cin >> rows[i][j], rows[i][j]--;
    vector<vector<set<int>>> occs(3, vector<set<int>>(n));
    rep(i, 3)
    {
        rep(j, n) occs[i][rows[i][j]].insert(j);
    }

    auto isgood = [&](int x)
        {
            bool good = 1;
            rep(i, 3) good &= sz(occs[i][x]) > 0;
            return good;
        };

    vi numsz(n);
    rep(i, 3) rep(j, n) numsz[j] += sz(occs[i][j]) > 0;
    vi q;
    vi vis(n);
    rep(i, n)
    {
        if (!isgood(i))
        {
            rep(j, 3)
            {
                repe(u, occs[j][i]) if (!vis[u]) q.push_back(u), vis[u] = 1;
            }
        }
    }
    
    int ans = 0;
    while (sz(q))
    {
        int u = q.back();
        q.pop_back();


        ans++;

        rep(i, 3)
        {
            int v = rows[i][u];
            occs[i][v].erase(u);
            if (!isgood(v))
            {
                rep(j, 3)
                {
                    while (sz(occs[j][v]))
                    {
                        int x = *begin(occs[j][v]);
                        if (!vis[x])
                        {
                            vis[x] = 1;
                            q.push_back(x);
                        }
                        occs[j][v].erase(occs[j][v].begin());
                    }
                }
            }
        }
    }
    cout << ans;

    return 0;
}
