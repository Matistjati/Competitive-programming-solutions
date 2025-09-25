#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = ll(1e18);
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll,ll>;

#define rep(i,b) for(int i = 0; i < (b); i++)
#define repp(i,a,b) for(int i = (a); i < (b); i++)
#define repe(i,a) for(auto& i : a)
#define sz(x) ((int)x.size())

ll dp[2][2][20];
ll dpd[2][2][20];
ll cnt(int i, int digit, bool prefzero, bool unbounded, vi& lim)
{
    if (i==sz(lim))
    {
        if (digit!=0) return 0;
        if (digit==0)
        {
            if (prefzero) return -30;
            return 0;
        }
    }
    ll& v = dp[prefzero][unbounded][i];
    if (dpd[prefzero][unbounded][i]) return v;
    ll ret = 0;
    int ub = unbounded ? 10 : lim[i]+1;
    rep(v,ub)
    {
        ret = max(ret, (v==digit) + cnt(i+1, digit, prefzero&(v==0), unbounded || (v<lim[i]), lim));
    }

    dpd[prefzero][unbounded][i] = 1;
    return v=ret;
}

int main() {
    ll amount[10] = {0};
    amount[0]=1;
    string x;
    cin >> x;
    vi lim;
    for (char c : x)
    {
        lim.push_back(int(c-'0'));
    }

    rep(d, 10)
    {
        memset(dp,0,sizeof(dp));
        memset(dpd,0,sizeof(dpd));
        amount[d] = max(amount[d], cnt(0,d,1,0,lim));
    }
    int ans = 0;
    rep(i,10) ans += amount[i];
    cout << ans << '\n';

    return 0;
}

