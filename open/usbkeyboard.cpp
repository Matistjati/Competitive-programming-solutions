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

vvi dp(ll(1e5)+10, vi(7,-1));
ll best(ll index, ll sent, string& in)
{
    if (index == in.size())
    {
        return 0;
    }

    ll& v = dp[index][sent];
    if (v != -1) return v;

    ll ret = inf;
    if (index==0)
    {
        ret = 1+best(index + 1, sent + 1, in);
    }
    else
    {
        if (in[index]>in[index-1])
        {
            if (sent<6)
            {
                ret = min(ret, best(index + 1, sent + 1, in));
            }
            else
            {
                ret = min(ret, 1 + best(index + 1, 1, in));
            }
        }
        ret = min(ret, 1 + best(index + 1, 1, in));
    }

    return (v=ret);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    string in;
    cin >> in;

    cout << best(0, 0, in);

    return 0;
}
