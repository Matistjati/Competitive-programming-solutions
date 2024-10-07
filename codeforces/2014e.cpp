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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

typedef tuple<int, int, int> p3;
vi dist(vector<vector<p2>>& edges, vi& horse, int s)
{
    
    vvi dist(2, vi(sz(horse), inf));
    priority_queue<p3> pq;
    pq.emplace(0, 0, s);
    while (sz(pq))
    {
        int d, mounted, u;
        tie(d, mounted, u) = pq.top();
        pq.pop();

        mounted |= horse[u];

        if (dist[mounted][u] != inf) continue;
        dist[mounted][u] = -d;

        repe(e, edges[u])
        {
            pq.emplace(d - e.second / (mounted?2:1), mounted, e.first);
        }
    }
    vi ret(sz(horse), inf);
    rep(i, sz(horse)) ret[i] = min(dist[0][i], dist[1][i]);
    return ret;
}

signed main()
{
    fast();


    int t;
    cin >> t;
    while (t--)
    {
        int n, m, h;
        cin >> n >> m >> h;
        vi horse(n);
        rep(i, h)
        {
            int u;
            cin >> u;
            horse[u - 1] = 1;
        }
        vector<vector<p2>> edges(n);
        rep(i, m)
        {
            int a, b, w;
            cin >> a >> b >> w;
            a--; b--;
            edges[a].emplace_back(b, w);
            edges[b].emplace_back(a, w);
        }
        vi a = dist(edges, horse, 0);
        vi b = dist(edges, horse, n-1);
        int ans = inf;
        rep(i, n) ans = min(ans, max(a[i], b[i]));
        if (ans==inf)
        {
            cout << "-1\n";
        }
        else cout << ans << "\n";
    }

    return 0;
}
