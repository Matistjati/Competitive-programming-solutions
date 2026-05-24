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

int dp[1<<20];

int n;
vi adj;
int solve(int mask) {
    if (mask == (1<<n)-1) {
        return 0;
    }
    if (dp[mask]!=-1) return dp[mask];

    int ret = -1000000;
    rep(i,n) {
        if (mask & (1<<i)) continue;
        unsigned int gain = adj[i] & mask;
        unsigned int loss = adj[i] & (~mask);
        ret = max(ret, (int)popcount(gain)-popcount(loss)-solve(mask|(1<<i)));
    }
    return dp[mask]=ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(dp,-1,sizeof(dp));

    int m;
    cin >> n >> m;
    adj.resize(n);
    rep(i,m) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        adj[a] |= 1<<b;
        adj[b] |= 1<<a;
    }

    int delta = solve(0);
    cerr << "delta=" << delta << '\n';
    if (delta==0) cout << "tie\n";
    else if (delta>0) cout << "player 1\n";
    else cout << "player 2\n";

    return 0;
}
