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

vector<int> val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for (auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e,g,f));

    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i,n) if (comp[i] < 0) dfs(i, g, f);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m;
    cin >> n >> m;
    vi coins(n);
    rep(i,n) cin >> coins[i];
    vi dp(n, -inf);
    dp[n-1]=coins[n-1];

    vvi adj(n);
    rep(i,m) {
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    scc(adj, [&](vector<int> comp) {
        ll compval = -inf;
        repe(u,comp) {
            repe(e,adj[u]) {
                compval = max(compval,dp[e]);                
            }
        }
        repe(u,comp) compval += coins[u];
        repe(u,comp) dp[u] = compval;
    });
    cout << dp[0] << '\n';

    return 0;
}

