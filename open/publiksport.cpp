#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
const ll inf = 1e18;
using p2 = pair<ll, ll>;

#define repe(i, arr) for (auto& i : arr)
#define rep(i, b) for(ll i = 0; i < (b); ++i)
#define repp(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)x.size())

int k;
ll ans = -1;

template<class F>
struct Centroid {
    vector<vi> adj;
    vi cnt;
    F f;
    Centroid(const vector<vi>& adj, F f) : adj(adj),
        cnt(sz(adj),-1), f(f) {
        dfs(0, -1);
    }
    void calc_sz(int u, int p) {
        cnt[u] = 1;
        for (int e : adj[u])
            if (e != p) calc_sz(e, u), cnt[u] += cnt[e];
    }
    int find_centroid(int u, int p, int n) {
        for (int e : adj[u])
            if (e != p && cnt[e] > n / 2)
                return find_centroid(e, u, n);
        return u;
    }
    void dfs(int u, int p) {
        calc_sz(u, -1);
        u = find_centroid(u, u, cnt[u]);
        f(u, p, adj);
        for (int e : adj[u]) {
            adj[e].erase(find(all(adj[e]), u));
            dfs(e, u);
        }
    }
};


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n >> k;

    vvi adj(n);
    rep(i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if (k == 1) {
        rep(i, n) ans = max(ans, sz(adj[i]));
        cout << ans << '\n';
        return 0;
    }

    vi deg(n);
    rep(i,n) deg[i]=sz(adj[i]);
    Centroid centroid(adj, [&](int u, int p, vvi& adj){
        vector<vector<p2>> deps(1); // depth -> list of profits
        int it = 0;
        auto gather = [&](auto&& self, int u, int p, int d, ll tot) -> void {
            tot += deg[u];
            if (d>=sz(deps)) deps.push_back({});
            deps[d].emplace_back(tot, it);

            repe(e,adj[u]) if (e!=p) self(self,e,u,d+1,tot);
        };
        repe(e,adj[u]) {
            gather(gather,e,u,0,0);
            it++;
        }
        // for each depth, find 2 largest
        vector<array<p2, 2>> best_two(sz(deps), {{{-inf,-1}, {-inf, -1}}});
        rep(i,sz(deps)) {
            auto& dep = deps[i];
            if (sz(dep)) best_two[i][0] = *max_element(all(dep));
            if (sz(dep)>1) {
                rep(j,sz(dep)) if (dep[j].second!=best_two[i][0].second) {
                    best_two[i][1]=max(best_two[i][1], dep[j]);
                }
            }
        }
        // one single path
        if (sz(best_two)>k-2) ans = max(ans, deg[u] + best_two[k-2][0].first);
        // path with u as lca
        rep(d, sz(best_two)) {
            int d2 = k-3-d;
            if (d2 < 0 || d2 >= sz(deps)) continue;
            for (auto me : best_two[d]) {
                for (auto other : best_two[d2]) {
                    if (me.second!=other.second) {
                        ans = max(ans, deg[u] + me.first + other.first);
                    }
                }
            }
        }
    });

    if (ans == -1) cout << "-\n";
    else cout << ans-2*(k-1) << '\n';

    return 0;
}
