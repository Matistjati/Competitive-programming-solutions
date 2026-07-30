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

struct ft {
    vi tree;
    ft(int n) : tree(n+1) {}

    void add(int i, int v) {
        for (i++; i < sz(tree); i += i&-i) tree[i] += v;
    }
    int query(int r) {
        int ret = 0;
        for (r++; r > 0; r-=r&-r) ret += tree[r];
        return ret;
    }
};

ft tree = ft(0);
ll tot_edges = 0;
void dfs(int u, int p, vvi& adj) {
    tot_edges += tree.query(u);
    tree.add(u,1);
    for (auto e : adj[u]) if (e!=p) dfs(e,u,adj);
    tree.add(u,-1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<p2> dfs_info;
    // cringe input format
    string line;
    while (getline(cin, line)) {
        int delim = line.find('/');
        dfs_info.emplace_back(stoi(line.substr(0,delim)), stoi(line.substr(delim+1)));
    }

    int n = sz(dfs_info);

    int root;
    vector<p2> st;
    vvi adj(n);
    for (auto [d,u] : dfs_info) {
        if (d==0) {
            root = u;
            st.emplace_back(u,d);
            continue;
        }
        while (st.back().second+1>d) st.pop_back();
        int e = st.back().first;
        adj[u].push_back(e);
        adj[e].push_back(u);
        st.emplace_back(u,d);
    }
    tree = ft(n);

    dfs(root,root,adj);

    ll ans = 1;
    const ll mod = 1e9+7;
    ll mul = 2;
    while (tot_edges) {
        if (tot_edges % 2) ans = ans*mul%mod;
        mul=mul*mul%mod;
        tot_edges /= 2;
    }
    
    cout << ans << '\n';

    return 0;
}
