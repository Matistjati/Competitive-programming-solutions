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

int tshirt(int n, int l[], int h[], int t[])
{
    int matches = 0;

    priority_queue<int> ending;
    priority_queue<p2> startpoints;
    rep(i, n) startpoints.emplace(-l[i], -h[i]);

    sort(t, t+n);

    rep(i, n)
    {
        while (startpoints.size() && -startpoints.top().first<=t[i])
        {
            ending.emplace(startpoints.top().second);
            startpoints.pop();
        }

        while (ending.size() && -ending.top() < t[i]) ending.pop();

        if (ending.size())
        {
            matches++;
            ending.pop();
        }
    }

    return matches;
}
