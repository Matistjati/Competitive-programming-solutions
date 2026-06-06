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
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    using bset = bitset<1000>;
    vector<bset> adj(n);
    bset leaf;
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        adj[a][b] = 1;
        adj[b][a] = 1;
        if (a == b) continue;
    }
    rep(i, n) if (adj[i].count() == 0) leaf[i] = 1;
    rep(i, n) adj[i][i] = 1;

    bset alive;
    rep(i, n) alive[i] = 1;
    rep(_, n) {
        bool any = 0;
        rep(i, n) { // try to kill i
            if (!alive[i]) continue;
            for (int j = adj[i]._Find_first(); j < 1000; j = adj[i]._Find_next(j)) {
                if (i == j) continue;
                if ((adj[i] & adj[j]) == adj[j]) {
                    any = 1;
                    alive[j] = 0;
                    rep(k, n) adj[k][j] = 0;
                    break;
                }
            }
        }
        if (!any) break;
    }

    int ans = 0;
    rep(i, n) if (leaf[i] || (alive[i] && adj[i].count() > 1)) {
        ans += i;
    }
    cout << ans << '\n';

    return 0;
}
