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

    ll n,k,x;
    cin >> n >> k >> x;

    vi nums(n);
    rep(i,n) cin >> nums[i];
    double ans = abs(x-accumulate(all(nums),0.)/double(n));
    ll tot = accumulate(all(nums),0LL);

    if (k>=1) {
        ll target = x*(n-1);
        ll best = inf;
        rep(i,n) {
            best = min(best, abs(target-(tot-nums[i])));
        }
        ans = min(ans, best/double(n-1));
    }
    if (k>=2) {
        ll target = x*(n-2);
        ll best = inf;
        rep(i,n) {
            repp(j,i+1,n) {
                best = min(best, abs(target-(tot-nums[i]-nums[j])));
            }
        }
        ans = min(ans, best/double(n-2));
    }

    if (k>=3) {
        set<ll> seen;
        ll target = x*(n-3)-tot;
        ll best = inf;
        rep(k,n) {
            repp(l,k+1,n) {
                // min abs(target-(tot-nums[k]-nums[l]-seen[x]))
                // min abs((target-tot)+nums[k]+nums[l]+seen[x]))
                ll t = target + nums[k]+nums[l];
                auto it = seen.lower_bound(-t);
                if (it!=seen.end()) best = min(best, abs(target+nums[k]+nums[l]+*it));
                if (it!=begin(seen)) best = min(best, abs(target+nums[k]+nums[l]+*prev(it)));
            }
            seen.insert(nums[k]);
        }
        ans = min(ans, best/double(n-3));
    }

    if (k>=4) {
        set<ll> seen;
        ll target = x*(n-4)-tot;
        ll best = inf;
        rep(k,n) {
            repp(l,k+1,n) {
                // min abs(target-(tot-nums[k]-nums[l]-seen[x]))
                // min abs((target-tot)+nums[k]+nums[l]+seen[x]))
                ll t = target + nums[k]+nums[l];
                auto it = seen.lower_bound(-t);
                if (it!=seen.end()) best = min(best, abs(target+nums[k]+nums[l]+*it));
                if (it!=begin(seen)) best = min(best, abs(target+nums[k]+nums[l]+*prev(it)));
            }
            rep(i,k) {
                int j = k;
                seen.insert(nums[i]+nums[j]);
            }
        }
        ans = min(ans, best/double(n-4));
    }

    cout << fixed << setprecision(15) << ans << '\n';

    return 0;
}
