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



int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vi nums(n);
    rep(i,n) cin >> nums[i];
    sort(all(nums));
    reverse(all(nums));
    if (n==1) {
        cout << nums[0] << '\n';
        return 0;
    }

    ll best = inf;
    auto cost = [&](int num_breaks) {
        ll mul = 1;

        int curr = num_breaks+1;
        ll c = num_breaks*3600;
        rep(i,n) {
            c += nums[i] * mul;
            curr--;
            if (c>1e15) break;
            if (curr==0) {
                mul*=2;
                curr=num_breaks+1;
            }
        }
        best = min(best,c);
        return c;
    };
    cost(n);

    int lo = -1;
    int hi = n+1;
    while (hi-lo>5) {
        int l = lo+(hi-lo)/3;
        int r = hi-(hi-lo)/3;

        ll cl = cost(l);
        ll cr = cost(r);
        if (cl>=cr) lo = l;
        else hi = r;
    }
    repp(i,max(0,lo),min(n,hi)) cost(i);

    cout << best << '\n';

    return 0;
}
