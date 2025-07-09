#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

#define rep(i, b) for(int i = 0; i < (b); i++)
#define repp(i, a, b) for(int i = a; i < (b); i++)
#define repe(i,arr) for (auto& i : arr)
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
typedef pair<int, int> p2;
typedef vector<int> vi;
typedef vector<vi> vvi;


signed main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<tuple<int, int, int>>> adj(n);
    rep(i, m)
    {
        int a, b, w;
        string m;
        cin >> a >> b >> w >> m;
        adj[a].emplace_back(b, w, m == "A380");
    }
    
    priority_queue<tuple<int,int,int>> pq;
    pq.emplace(0, 0, 0);
    vvi vis(2, vi(n));

    while (sz(pq))
    {
        auto [d, u, g] = pq.top();
        pq.pop();
        if (vis[g][u]) continue;
        vis[g][u] = 1;
        if (g==1 && u==n-1)
        {
            cout << -d << "\n";
            return 0;
        }
        for (auto [e, w, good] : adj[u])
        {
            pq.emplace(d - w, e, g || good);
        }
    }
    cout << "-1\n";

    return 0;
}

