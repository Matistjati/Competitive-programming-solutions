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

    int n,m;
    cin >> n >> m;

    vi adj(n);
    rep(i,m) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        adj[a] |= 1<<b;
        adj[b] |= 1<<a;
    }

    vi ans(n+1);
    rep(mask, 1<<n) {
        bool good = 1;

        rep(i,n) {
            if (!(mask&(1<<i))) continue;
            good &= (mask & adj[i]) == 0;
        }

        if (good) ans[popcount((unsigned int)mask)]++;
    }

    rep(i,n+1) cout << ans[i] << ' ';

    return 0;
}
