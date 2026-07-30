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

vi nums;
ll f(ll k)
{
    ll cost = 0;
    ll curr = k;
    rep(i, nums.size())
    {
        cost += curr;
        curr -= nums[i];
    }
    cost += curr;
    return abs(cost);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    rep(i, n)
    {
        ll k;
        cin >> k;
        nums.push_back(k);
    }

    ll b = 1e9;
    ll a = -1e9;
    while (b - a >= 5) {
        ll mid = (a + b) / 2;
        if (f(mid) >= f(mid + 1)) a = mid; // (A)
        else b = mid + 1;
    }
    repp(i, a + 1, b + 1) if (f(a) >= f(i)) a = i; // (B)

    rep(i, nums.size())
    {
        cout << a << " ";
        a -= nums[i];
    }
    cout << a << '\n';

    return 0;
}
