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

ll dp[2][int(2e5) + 10];
vi a, b;
ll ans(int i, int j)
{
    if (i == sz(a)) return 0;
    if (j >= sz(b)) return inf;
    ll& v = dp[j - i][i];
    if (v != -1) return v;

    ll ret = inf;

    if (j == i && j + 1 < sz(b)) ret = min(ret, abs(a[i] - b[j + 1]) + ans(i + 1, j + 2));
    ret = min(ret, abs(a[i] - b[j]) + ans(i + 1, j + 1));

    return v=ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    memset(dp, -1, sizeof(dp));

    int n, m;
    cin >> n >> m;
    a.resize(n);
    b.resize(m);
    repe(v, a) cin >> v;
    repe(v, b) cin >> v;
    sort(all(a));
    sort(all(b));

    cout << ans(0, 0) << '\n';

    return 0;
}
