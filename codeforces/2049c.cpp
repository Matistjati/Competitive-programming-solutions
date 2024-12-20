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
//#include <cassert>
#define assert(x) if (!(x)) __debugbreak()
#endif


void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    x--; y--;

    vvi adj(n);
    rep(i, n)
    {
        adj[i].push_back((i + 1) % n);
        adj[i].push_back((i - 1 + n) % n);

    }
    adj[x].push_back(y);
    adj[y].push_back(x);

    int mx = x%2;
    int my = y%2;

    auto mex = [&](int u, vi& a)
        {
            int occ[4];
            rep(i, 4) occ[i] = 0;
            repe(e, adj[u]) occ[a[e]]++;
            rep(i, 4) if (occ[i] == 0) return i;
        };
    if (mx!=my)
    {
        vi a(n);
        rep(i, n) a[i] = i % 2;
        if (n % 2) a.back() = 2;
        bool good = 1;
        rep(i, n) good &= a[i] == mex(i, a);
        if (good)
        {
            repe(u, a) cout << u << " ";
            cout << "\n";
            return;
        }
        assert(0);
    }
    else
    {
        if (mx==1)
        {
            vi a(n);
            rep(i, n) a[i] = i % 2;
            a[max(x, y)] = 2;
            a.back() = mex(n-1,a);
            bool good = 1;
            rep(i, n)
            {
                good &= a[i] == mex(i, a);
            }
            if (good)
            {
                repe(u, a) cout << u << " ";
                cout << "\n";
                return;
            }
            assert(0);
        }
        else
        {
            vi a(n);
            rep(i, n) a[i] = i % 2;
            
            a[max(x, y)] = 2;
            int p = 0;
            repp(i, max(x, y) + 1, n) a[i] = (p++) % 2;
            a.back() = mex(n - 1,a);
            bool good = 1;
            rep(i, n)
            {
                good &= a[i] == mex(i, a);
            }
            if (good)
            {
                repe(u, a) cout << u << " ";
                cout << "\n";
                return;
            }
            assert(0);
        }
        cout << "IDK\n";
    }
    return;




    rep(offset, 2)
    {
        vi a(n);
        rep(i, n) a[i] = (i + offset) % 3;

        bool good = 1;
        rep(i, n) good &= a[i] == mex(i, a);
        if (!good)
        {
            continue;
        }
        repe(u, a) cout << u << " ";
        cout << "\n";
        return;
    }
    assert(0);

}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
