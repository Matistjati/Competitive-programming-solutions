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
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int n, m;
    cin >> n >> m;
    vvi edges(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    queue<p2> q;
    vi vis(n);
    q.emplace(0, 0);

    while (sz(q))
    {
        int d, u;
        tie(d, u) = q.front();
        q.pop();

        if (vis[u]) continue;
        vis[u] = 1;

        if (u==n-1)
        {
            cout << max(0LL, d - 1);
            return 0;
        }
        repe(e, edges[u]) q.emplace(d + 1, e);
    }

    return 0;
}
