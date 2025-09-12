#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

int n, v;


vector<p2> positions;
ll dp[101][101];
ll dist(p2 a, p2 b)
{
    ll dx = a.first - b.first;
    ll dy = a.second - b.second;
    return dx * dx + dy * dy;
}
ll ans(int curr, int skips_left)
{
    if (curr == n-1)
    {
        return 0;
    }

    ll& v = dp[curr][skips_left];
    if (v != -1) return v;

    ll ret = inf;

    rep(skips, n + 1)
    {
        if (skips > skips_left) break;
        int j = curr + skips + 1;
        if (j >= n) break;
        ret = min(ret, dist(positions[curr], positions[j]) + ans(j, skips_left - skips));
    }

    return v = ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    memset(dp, -1, sizeof(dp));
    cin >> n >> v;

    positions.resize(n);
    repe(p, positions) cin >> p.first >> p.second;

    cout << ans(0, v)%ll(1e9+7) << '\n';

    return 0;
}
