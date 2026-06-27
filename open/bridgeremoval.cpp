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

int timer=0;
void dfs(int u, int p, vi& tin, vvi& adj) {
    tin[u] = timer++;
    repe(e,adj[u]) if (e!=p) dfs(e,u,tin,adj);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vvi adj(n);
    rep(i,n-1) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    vi tin(n);
    dfs(0,0,tin,adj);
    vi leafs;
    leafs.reserve(n);
    rep(i,n) if (sz(adj[i])==1) leafs.push_back(i);
    sort(all(leafs), [&](int a, int b) {
        return tin[a]<tin[b];
    });

    cout << (sz(leafs)+1)/2 << '\n';
    for (int i = 0; i * 2 < sz(leafs); i++) {
        cout << leafs[i]+1 << ' ' << leafs[(i+sz(leafs)/2)%sz(leafs)]+1 << '\n';
    }

    return 0;
}
