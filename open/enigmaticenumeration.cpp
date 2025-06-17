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

int n;
vector<vector<p2>> adj;
vi forbidden;
p2 num_shortest_paths(int a, int b)
{
    vi num_ways(n);
    vi dist(n,inf);
    num_ways[a] = 1;
    dist[a] = 0;

    queue<int> q;
    q.push(a);
    while (sz(q))
    {
        int u = q.front();
        q.pop();

        if (u == b) return { num_ways[b],dist[b] };

        repe(e, adj[u])
        {
            if (forbidden[e.second]) continue;
            if (num_ways[e.first] == 0)
            {
                dist[e.first] = dist[u] + 1;
                num_ways[e.first] += num_ways[u];
                q.emplace(e.first);
            }
            else if (dist[u] + 1 == dist[e.first])
            {
                num_ways[e.first] += num_ways[u];
            }
        }
    }

    return { num_ways[b],dist[b] };
}

signed main()
{
    fast();

    int m;
    cin >> n >> m;
    adj.resize(n);
    vector<p2> edges(m);
    forbidden.resize(m);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[i] = { a,b };
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
    }

    int shortest = inf;
    rep(i, m)
    {
        forbidden[i] = 1;
        p2 e = edges[i];
        shortest = min(shortest, num_shortest_paths(e.first, e.second).second);
        forbidden[i] = 0;
    }
    int ans = 0;
    rep(i, sz(edges))
    {
        forbidden[i] = 1;
        auto [a, b] = edges[i];
        p2 c = num_shortest_paths(a, b);
        if (c.second == shortest) ans += c.first;
    }
    cout << ans;


    return 0;
}
