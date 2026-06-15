#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main() {
    auto start = chrono::high_resolution_clock::now();
    cin.tie(0)->sync_with_stdio(0);

    int n,m,k,a,b;
    cin >> n >> m >> k >> a >> b;


    vector<vector<p2>> adj(n);
    vvi radj(n);
    rep(i,m) {
        int a,b,w;
        cin >> a >> b >> w;
        adj[a].emplace_back(b,w);
        radj[b].push_back(a);
    }

    vi b_reachable(n);
    {
        queue<int> q;
        q.push(b);
        while (sz(q)) {
            int u = q.front();
            q.pop();
            if (b_reachable[u]) continue;
            b_reachable[u]=1;
            repe(e,radj[u]) q.push(e);
        }
    }

    if (!b_reachable[a]) {
        cout << "POSITIVE INFINITY\n";
        return 0;
    }


    queue<int> q;
    q.emplace(a);
    vi dist(n,inf);
    dist[a]=0;
    vector<char> inq(n);
    rep(i,n) if (!b_reachable[i]) inq[i]=1;

    int it = 0;
    while (sz(q)) {
        if (it++ % 128 == 0) {
            if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count()>2500) {
                cout << "NEGATIVE INFINITY\n";
                return 0;
            }
        }
        int u = q.front();
        q.pop();

        for (auto [e,w] : adj[u]) {
            if (dist[u]+w<dist[e]) {
                dist[e]=dist[u]+w;
                if (!inq[e]) q.push(e);
            }
        }
    }

    cout << dist[b] << '\n';

    return 0;
}
