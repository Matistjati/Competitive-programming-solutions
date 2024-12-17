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


    auto ask = [](vi x)
        {
            cout << "? " << sz(x) << " ";
            repe(u, x) cout << u+1 << " ";
            cout << endl;
            int resp;
            cin >> resp;
            return resp;
        };

    vi deg(n);
    rep(i, n) deg[i] = ask({ i });

    vvi adj(n, vi(n));
    rep(i, n)
    {
        repp(j, i + 1, n)
        {
            if (ask({i,j})!=deg[i]+deg[j])
            {
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
        }
    }
    cout << "!\n";
    rep(i, n)
    {
        rep(j, n)
        {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }


    return 0;
}
