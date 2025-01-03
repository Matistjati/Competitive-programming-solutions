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

    int n, k;
    cin >> n >> k;

    vector<string> in(n);
    rep(i, n) cin >> in[i];

    auto buildpref = [&](vvi mat)
        {
            vvi ret(n, vi(n));

            rep(i, n)
            {
                rep(j, n)
                {
                    ret[i][j] = mat[i][j];
                    if (i) ret[i][j] += ret[i - 1][j];
                    if (j) ret[i][j] += ret[i][j - 1];
                    if (i && j) ret[i][j] -= ret[i - 1][j - 1];
                }
            }

            return ret;
        };

    vvi profit(n, vi(n));
    rep(i, n) rep(j, n)
    {
        char v = in[i][j];
        if (v >= '0' && v <= '9') profit[i][j] = v - '0';
    }
    
    vvi blocked(n, vi(n));
    rep(i, n) rep(j, n)
    {
        char v = in[i][j];
        if ((v >= '0' && v <= '9') || v == '#') blocked[i][j] = 1;
    }

    vvi profitpref = buildpref(profit);
    vvi blockedpref = buildpref(blocked);

    auto squaresum = [&](vvi& pref, int rol, int ror, int col, int cor)
        {
            int ret = pref[ror][cor];
            if (col) ret -= pref[ror][col - 1];
            if (rol) ret -= pref[rol - 1][cor];
            if (col && rol) ret += pref[rol - 1][col - 1];
            return ret;
        };

    int ans = 0;
    rep(i, n - k + 1)
    {
        rep(j, n - k + 1)
        {
            auto good = squaresum(blockedpref, i, i + k - 1, j, j) == 0;
            good &= squaresum(blockedpref, i, i + k - 1, j+k-1, j+k-1) == 0;
            good &= squaresum(blockedpref, i, i, j, j+k-1) == 0;
            good &= squaresum(blockedpref, i+k-1, i+k-1, j, j+k-1) == 0;
            if (good)
            {
                ans = max(ans, squaresum(profitpref, i + 1, i + k - 2, j + 1, j + k - 2));
            }
        }
    }
    cout << ans;

    return 0;
}
