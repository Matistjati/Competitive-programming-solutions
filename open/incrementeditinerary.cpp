#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll,ll>;
#define rep(i,n) for (int i = 0; i < (n); i++)
const ll inf = 1e18;
#define sz(x) ((ll)x.size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m;
    cin >> n >> m;

    vector<pair<int,int>> edg(m);
    vvi adj(n);
    rep(i,m) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edg[i] = {a,b};
    }

    auto bfs = [&](int s) {
        vector<int> dist(n, 1e9);
        queue<pair<int,int>> q;
        q.emplace(0,s);
        dist[0]=0;
        while (sz(q)) {
            auto [d,u] = q.front();
            q.pop();
            if (d > dist[u]) continue;
            for (auto e : adj[u]) {
                if (d+1 < dist[e]) {
                    dist[e]=d+1;
                    q.emplace(d+1,e);
                }
            }
        }
        return dist;
    };

    vector<int> from_start = bfs(0);
    vector<int> to_goal = bfs(n-1);

    int t_dist = from_start.back();
    for (auto [a,b] : edg) {
        if (from_start[a] > from_start[b]) swap(a,b);
        if (from_start[a] + to_goal[b] == t_dist) {
            cout << "possible\n";
            return 0;
        }
    }
    cout << "impossible\n";


    return 0;
}
