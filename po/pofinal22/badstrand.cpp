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

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n, b;
    cin >> n >> b;
    vi arr(n);
    repe(v, arr) cin >> v;

    ll ans = 0;
    int j = 0;
    ll cost = 0;
    rep(i, n)
    {
        while (j<n&&cost+arr[j]<=b)
        {
            cost += arr[j];
            j++;
        }
        ans = max(ans, j - i);
        cost -= arr[i];
    }

    cout << ans;

    return 0;
}
