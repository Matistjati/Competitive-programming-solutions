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

struct UF {
    vi par;
    UF(int n) : par(n) {iota(all(par),0);}
    int find(int x) {return par[x]==x?x:par[x]=find(par[x]);}
    void merge(int a, int b) {
        par[find(a)]=find(b);
    }
};

const int MAXN = 5e4, lg=17;
int up[lg][MAXN];
int tin[MAXN],tout[MAXN];
int timer=0;

void dfs(int u, int p, vvi& adj) {
    up[0][u]=p;
    repp(d,1,lg) {
        up[d][u]=up[d-1][up[d-1][u]];
    }
    tin[u] = timer++;
    for (auto e : adj[u]) if (e!=p) dfs(e,u,adj);
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,q;
    cin >> n >> q;

    vvi adj(n);
    vector<p2> extra;
    UF uf(n);
    rep(i,n+1) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        if (uf.find(a)!=uf.find(b)) {
            adj[a].push_back(b);
            adj[b].push_back(a);
            uf.merge(a,b);
        }
        else {
            extra.emplace_back(a,b);
            extra.emplace_back(b,a);
        }
    }

    dfs(0,0,adj);

    
    while (q--) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        

        int ans = 1;

        auto path_isect = [&](this auto path_isect, p2 a, p2 b) {
            if (isancestor(a.second,a.first)) swap(a.first,a.second);
            if (isancestor(a.first,a.second)) {
                if (isancestor(b.second,b.first)) swap(b.first,b.second);
                if (isancestor(b.first,b.second)) {
                    if (isancestor(b.first,a.first)) {
                        return isancestor(a.first,b.second);
                    }
                    else {
                        return isancestor(a.first,b.first) && isancestor(b.first,a.second);
                    }
                }
                else {
                    int lc = lca(b.first,b.second);
                    return path_isect(a,{lc,b.first}) || path_isect(a,{lc,b.second});
                }
            }
            else {
                int lc = lca(a.first,a.second);
                return path_isect({lc,a.first},b) || path_isect({lc,a.second},b);
            }
        };

        auto check_paths = [&](vector<p2>& paths) {
            rep(i,sz(paths)) {
                repp(j,i+1,sz(paths)) {
                    if (path_isect(paths[i],paths[j])) return false;
                }
            }
            return true;
        };

        for (p2 c1 : extra) {
            for (p2 c2 : extra) {
                vector<p2> paths = {{a,c1.first},{c1.second,c2.first},{c2.second,b}};
                ans += check_paths(paths);
            }

            {
                vector<p2> paths = {{a,c1.first},{c1.second,b}};
                ans += check_paths(paths);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
