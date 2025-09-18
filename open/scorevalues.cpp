#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repp(i, a, b) for(int i = a; i < (b); i++)
#define rep(i, a) for(int i = 0; i < (a); i++)
#define repe(i, x) for (auto& i : x)
#define all(x) begin(x), end(x)
#define sz(x) ((ll)(x).size())
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> pii;

const ll cutoff = int(4e6 + 11);
ll maxval, n;

ll dp[2][2][2][20][1002];
int g;
ll count(int digit, bool allzero, int goaldigit1, int goaldigit2, bool unlimited, bool free_below, ll rem, vi& limiter_up,
    vi& limiter_down)
{
    if (digit == sz(limiter_up))
    {
        return (allzero || rem != 0) ? -1000 : 0;
    }

    ll& v = dp[free_below][allzero][unlimited][digit][rem];
    if (v != -1) return v;
    ll ret = -1000;

    int ub = unlimited ? 10 : limiter_up[digit] + 1;
    int lb = free_below ? 0 : limiter_down[digit];
    ll power = 1;
    rep(i, sz(limiter_up) - digit - 1) power = (10 * power) % g;
    repp(d, lb, ub)
    {
        int inc;
        if (goaldigit1 == 0) inc = allzero || d != 0 ? 0 : 1;
        else inc = d == goaldigit1 || d == goaldigit2;

        ll newrem = (rem + d * power) % g;
        ret = max(ret, inc + count(digit + 1, allzero && (d == 0), goaldigit1, goaldigit2, unlimited || (d + 1 < ub), free_below || (d > lb), newrem,
            limiter_up, limiter_down));
    }

    return v = ret;
}

ll count_digit(ll upper_bound, int digit1, int digit2)
{
    memset(dp, -1, sizeof(dp));
    vi limiter_up;
    while (upper_bound)
    {
        limiter_up.push_back(upper_bound % 10);
        upper_bound /= 10;
    }
    reverse(all(limiter_up));
    ll c = cutoff;
    vi limiter_down;
    while (c)
    {
        limiter_down.push_back(c % 10);
        c /= 10;
    }
    while (sz(limiter_down) < sz(limiter_up)) limiter_down.push_back(0);
    reverse(all(limiter_down));
    string x;
    return count(0, 1, digit1, digit2, 0, 0, 0, limiter_up, limiter_down);
}


int main() {
    //cin.tie(0)->sync_with_stdio(0);
    //cin.exceptions(cin.failbit);

    cin >> maxval >> n;
    vi nums(n);
    repe(v, nums) cin >> v;

    vi dp(cutoff);
    if (maxval < cutoff) dp[maxval] = 1;
    dp[0] = 1;
    rep(i, cutoff)
    {
        if (!dp[i]) continue;
        repe(v, nums)
        {
            if (i + v < cutoff) dp[i + v] = 1;
        }
    }

    vi ans(10);
    ans[0] = 1;

    auto getcnt = [](ll x)
        {
            vi cnt(10);
            while (x)
            {
                cnt[x % 10]++;
                x /= 10;
            }
            return cnt;
        };

    rep(i, min(maxval + 1, cutoff))
    {
        if (!dp[i]) continue;
        vi x = getcnt(i);
        rep(j, 9) ans[j] = max(ans[j], x[j]);
        ans[6] = max(ans[6], x[6] + x[9]);
    }

    vi x = getcnt(maxval);
    rep(j, 9) ans[j] = max(ans[j], x[j]);
    ans[6] = max(ans[6], x[6] + x[9]);

    g = nums[0];
    repe(v, nums) g = gcd(g, v);

    if (maxval >= cutoff)
    {
        rep(i, 9)
        {
            ans[i] = max(ans[i], count_digit(maxval, i, i == 6 ? 9 : -1));
        }
    }

    rep(i, 9)
    {
        if (ans[i]) cout << i << " " << ans[i] << '\n';
    }
}
