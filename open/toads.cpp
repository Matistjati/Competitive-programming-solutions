#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ() {}
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j,sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vector<int> time, path, ret, vis;
    vi depth;
    RMQ<int> rmq;

    LCA(vector<vector<p2>>& C) : time(sz(C)+1), depth(sz(C)+1), vis(sz(C)+1) {
        int fake = sz(C);
        time[fake] = T++;
        rep(i,sz(C)) {
            if (vis[i]) continue;
            path.push_back(fake);
            ret.push_back(time[fake]);
            dfs(C, i,-1);
        }
        rmq = RMQ<int>(ret);
    }
    void dfs(vector<vector<p2>>& C, int v, int par) {
        vis[v]=1;
        time[v] = T++;
        for (auto [y,w] : C[v]) if (y != par) {
            depth[y]=depth[v]+w;
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }

    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    ll dist(ll a,ll b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

struct UF {
    vi par;
    UF(ll n) : par(n) {iota(all(par),0);}
    ll find(ll x) {return par[x]==x?x:par[x]=find(par[x]);}
    void merge(ll a, ll b) {
        a=find(a);b=find(b);
        par[b]=a;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    UF uf(n);

    vector<tuple<ll,ll,ll>> non_tree;
    vector<vector<p2>> treeadj(n);
    rep(i,n) {
        ll j,t;
        cin >> j >> t;
        j--;

        if (uf.find(i)!=uf.find(j)) {
            uf.merge(i,j);
            treeadj[i].emplace_back(j,t);
            treeadj[j].emplace_back(i,t);
        }
        else {
            non_tree.emplace_back(i,j,t);
        }
    }
    ll l;
    cin >> l;
    rep(i,l) {
        ll a,b,t;
        cin >> a >> b >> t;
        a--; b--;
        if (uf.find(a)!=uf.find(b)) {
            uf.merge(a,b);
            treeadj[a].emplace_back(b,t);
            treeadj[b].emplace_back(a,t);
        }
        else {
            non_tree.emplace_back(a,b,t);
        }
    }

    LCA lca(treeadj);

    map<ll,vector<tuple<ll,ll,ll>>> comp_nontree;
    for (auto [a,b,t] : non_tree) {
        assert(uf.find(a)==uf.find(b));
        comp_nontree[uf.find(a)].emplace_back(a,b,t);
    }

    ll q;
    cin >> q;
    while (q--) {
        ll a,b;
        cin >> a >> b;
        a--; b--;
        if (uf.find(a)!=uf.find(b)) {
            cout << "-1\n";
            continue;
        }
        ll comp = uf.find(a);
        vector<tuple<ll,ll,ll>>& nontree = comp_nontree[comp];

        ll numnodes = sz(nontree)*2+2;
        vi dist(numnodes,inf);
        auto get = [&](ll x) -> ll {
            if (x<2*sz(nontree)) {
                auto [a,b,_] = nontree[x/2];
                return x%2==0?a:b;
            }
            if (x==2*sz(nontree)) return a;
            if (x==2*sz(nontree)+1) return b;
            assert(0);
        };
        vector<vector<p2>> adj(numnodes);
        rep(i,sz(nontree)) {
            auto [a,b,w] = nontree[i];
            adj[i*2].emplace_back(i*2+1,w);
            adj[i*2+1].emplace_back(i*2,w);
        }
        rep(i,numnodes) {
            rep(j,numnodes) {
                adj[i].emplace_back(j, lca.dist(get(i),get(j)));
            }
        }
        dist[sz(dist)-2]=0;
        priority_queue<pair<ll,ll>> pq;
        pq.emplace(0, sz(dist)-2);
        while (sz(pq)) {
            auto [d,u] = pq.top();
            pq.pop();
            d=-d;
            if (d>dist[u]) continue;
            for (auto [e,w] : adj[u]) {
                if (w+d<dist[e]) {
                    dist[e]=w+d;
                    pq.emplace(-(w+d),e);
                }
            }
        }

        assert(dist.back()!=inf);

        cout << dist.back() << '\n';
    }

    return 0;
}
