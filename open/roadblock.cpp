#include <bits/stdc++.h>
using namespace std;

#define repe(i, arr) for (auto& i : arr)
#define rep(i, b) for(int i = 0; i < (b); ++i)
#define repp(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) ((int)x.size())
typedef long long ll;
using vi = vector<ll>;
using vvi = vector<vi>;
const ll inf = 1e18;
using p2 = pair<int,int>;

struct dominator_tree {
    vector<basic_string<int>> g, rg, bucket;
    basic_string<int> arr, par, rev, sdom, dom, dsu, label;
    int n, t;
    dominator_tree(int n)
        : g(n), rg(n),bucket(n),arr(n,-1),par(n,-1),rev(n,-1),
          sdom(n,-1),dom(n,-1),dsu(n,0),label(n,0),n(n),t(0){}
    void add_edge(int u, int v) { g[u] += v; }
    void dfs(int u) {
        arr[u] = t;
        rev[t] = u;
        label[t] = sdom[t] = dsu[t] = t;
        t++;
        for (int w : g[u]) {
            if (arr[w] == -1) {
                dfs(w);
                par[arr[w]] = arr[u];
            }
            rg[arr[w]] += arr[u];
        }
    }
    int find(int u, int x = 0) {
        if (u == dsu[u]) return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if (v < 0) return u;
        if (sdom[label[dsu[u]]] < sdom[label[u]])
            label[u] = label[dsu[u]];
        dsu[u] = v;
        return x ? v : label[u];
    }
    vector<int> run(int root) {
        dfs(root);
        iota(dom.begin(), dom.end(), 0);
        for (int i = t - 1; i >= 0; i--) {
            for (int w : rg[i])
                sdom[i] = min(sdom[i], sdom[find(w)]);
            if (i) bucket[sdom[i]] += i;
            for (int w : bucket[i]) {
                int v = find(w);
                if (sdom[v] == sdom[w])
                    dom[w] = sdom[w];
                else
                    dom[w] = v;
            }
            if (i > 1) dsu[i] = par[i];
        }
        for (int i = 1; i < t; i++) {
            if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
        }
        vector<int> outside_dom(n, -1);
        for (int i = 1; i < t; i++)
            outside_dom[rev[i]] = rev[dom[i]];
        return outside_dom;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    
    int n, m;
    cin >> n >> m;
    vi distrib(n);
    repe(u, distrib) cin >> u;

    vector<p2> edges;
    vvi adj(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges.emplace_back(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    priority_queue<p2> pq;
    vi dist(n, inf);
    dist[0] = 0;
    pq.emplace(0, 0);
    vi vis(n);
    while (sz(pq))
    {
        ll d, u;
        tie(d, u) = pq.top();
        pq.pop();
        d = -d;
        if (vis[u]) continue;
        vis[u] = 1;
        dist[u] = d;
        repe(e, adj[u])
        {
            pq.emplace(-(1 + d), e);
        }
    }

    vi is_critical(m);
    int i = 0;
    vector<vector<p2>> dagadj(n);
    dominator_tree tree(n+m);

    int e_ind = n;
    vi w(n+m);
    rep(i,n) w[i] = distrib[i];
    vi which_node(m, -1);
    for (auto [a, b] : edges)
    {
        if (abs(dist[a]-dist[b])==1)
        {
            is_critical[i] = 1;
            if (dist[a] > dist[b])
            {
                int intermediate = e_ind++;
                which_node[i] = intermediate;
                tree.add_edge(b,intermediate);
                tree.add_edge(intermediate,a);
                dagadj[b].emplace_back(a, i);
            }
            else
            {
                int intermediate = e_ind++;
                which_node[i] = intermediate;
                tree.add_edge(a,intermediate);
                tree.add_edge(intermediate,b);
                dagadj[a].emplace_back(b, i);
            }
        }
        i++;
    }
    vector<int> pars = tree.run(0);
    vvi tree_adj(sz(pars));
    rep(i,sz(pars))
    {
        int p = pars[i];
        if (i==p||p==-1) continue;
        tree_adj[i].push_back(p);
        tree_adj[p].push_back(i);
    }

    vi save(n+m);
    function<ll(int, int)> dfs = [&](int u, int p)
    {
        ll ret = w[u];

        repe(e,tree_adj[u]) if (e!=p) ret+=dfs(e,u);

        save[u] = ret;
        return ret;
    };
    ll base = dfs(0,0);


    rep(i, m)
    {
        if (is_critical[i])
        {
            assert(which_node[i]!=-1);
            ll reachable = 0;

            cout << save[which_node[i]] << '\n';
        }
        else cout << "0\n";
    }

    return 0;
}
