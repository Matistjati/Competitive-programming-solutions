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

pair<ll, ll> howlong(vector< pair<ll, ll>>& memo, ll N, char x[], ll pos, bool first, ll s)
{
    if (pos == N)
    {
        return { 0,pos};
    }

    pair<ll, ll>& v = memo[(pos * 2) + first];

    if (v.first != -1)
    {
        ll sum = v.first;

        sum += (x[pos] == 'a') * (v.second - pos);

        return {sum,v.second};
    }

    if (pos > 0 && !first && x[pos-1] == x[pos] && x[pos] == 'a')
    {
        return { 0,pos };
    }

    s += x[pos] == 'a';

    pair<ll, ll> r = howlong(memo, N, x, pos + 1, false, s);

    memo[(pos * 2) + first] = r;

    r.first += (x[pos] == 'a') * (r.second - pos);

    return r;
}

ll fibonacci(int N, char X[])
{
    ll ans = 0;
    vector< pair<ll, ll>> memo(N*2, {-1,-1});
    rep(i, N)
    {
        ans += get<0>(howlong(memo, N, X, i, true, 0));
    }
    return ans;
}
