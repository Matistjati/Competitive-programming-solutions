#pragma optimize("ofast")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define rep(i,lo,hi) for (int i =lo;i<hi;i++)
typedef tuple<int, int, int> p3;
typedef pair<ll, ll> p2;

int main()
{
    ll n, c;
    cin >> n >> c;
    vector<ll> days;
    rep(i, 0, n)
    {
        ll v;
        cin >> v;
        days.push_back(v);
    }

    vector<ll> ans(n);
    ll upright;
    ll upleft;
    rep(i, 0, n)
    {
        if (i == 0)
        {
            ans[i] = 0;
            upright = -days[i];
            upleft = days[i];
        }
        else
        {
            ll v = max(days[i] + upright, -days[i] + upleft) - c * i;
            v = max(v, 0LL);
            ans[i] = v;

            upright = max(upright, -days[i] + c * i);
            upleft = max(upleft, days[i] + c * i);
        }
    }

    rep(i, 0, n)
    {
        cout << ans[i] << " ";
    }

    return 0;
}