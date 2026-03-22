#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define repe(i, arr) for (auto& i : arr)
#define rep(i, b) for(ll i = 0; i < (b); ++i)
#define repp(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)x.size())

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, v;
    cin >> n >> v;

    vi h(n);
    rep(i, n) cin >> h[i];

    vi sufmax = h;
    ll m = 0;
    for (int i = n - 2; i >= 0; i--) sufmax[i]=max(sufmax[i],sufmax[i+1]);

    vi ans;
    int currh = v;

    rep(i, n)
    {
        if (h[i]>currh)
        {
            currh += 1;
            ans.push_back(sufmax[i]);
        }
    }
    cout << sz(ans) << '\n';
    repe(v, ans) cout << v << ' ';

    return 0;
}
