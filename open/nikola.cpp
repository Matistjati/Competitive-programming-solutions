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

vi costs;
int dp[1001][1001];
int solve(int i, int d) {
    if (i==sz(costs)-1) return 0;
    int& v = dp[i][d];
    if (v!=-1) return v;

    int ret = 1e9;
    if (i+d+1<sz(costs)) ret = min<int>(ret, costs[i+d+1]+solve(i+d+1,d+1));
    if (i-d>=0) ret = min<int>(ret, costs[i-d]+solve(i-d,d));
    return v=ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    memset(dp,-1,sizeof(dp));
    int n;
    cin >> n;
    costs.resize(n);
    rep(i,n) cin >> costs[i];

    cout << costs[1]+solve(1,1) << '\n';


    return 0;
}
