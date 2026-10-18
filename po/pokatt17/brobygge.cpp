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

const int MAXN = 1e5, lg=18;
int up[lg][MAXN];
int tin[MAXN],tout[MAXN],depth[MAXN];
int timer=0;

void dfs(int u, int p, vector<vector<p2>>& adj) {
    up[0][u]=p;
    repp(d,1,lg) {
        up[d][u]=up[d-1][up[d-1][u]];
    }
    tin[u] = timer++;
    for (auto [e,d] : adj[u]) if (e!=p) {
        depth[e] = depth[u]+d;
        dfs(e,u,adj);
    }
    tout[u] = timer++;
}

bool isancestor(int a, int b) {
    return tin[a]<=tin[b]&&tout[a]>=tout[b];
}

int lca(int a, int b) {
    if (isancestor(a,b)) return a;
    if (isancestor(b,a)) return b;

    for (int d = lg-1; d>=0; d--) {
        if (!isancestor(up[d][a],b)) {
            a=up[d][a];
        }
    }
    return up[0][a];
}

int dist(int a, int b) {
    return depth[a]+depth[b]-2*depth[lca(a,b)];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<p2>> adj(n);
    using t3 = tuple<int,int,int>;
    vector<t3> extra;
    rep(i,n-1) {
        int a,b,d;
        cin >> a >> b >> d;
        adj[a].emplace_back(b,d);
        adj[b].emplace_back(a,d);
    }

    int e;
    cin >> e;
    rep(i,e) {
        int a,b,d;
        cin >> a >> b >> d;
        extra.emplace_back(a,b,d);
        extra.emplace_back(b,a,d);
    }

    depth[0]=0;
    dfs(0,0,adj);

    int q;
    cin >> q;
    while (q--) {
        int s,t;
        cin >> s >> t;

        int ans = dist(s,t);

        for (auto [a,b,d1] : extra) {
            for (auto [e,f,d2] : extra) {
                ans = min(ans, dist(s,a)+d1+dist(b,e)+d2+dist(f,t));
            }

            ans = min(ans, dist(s,a)+d1+dist(b,t));
        }

        cout << ans << '\n';
    }

    return 0;
}
