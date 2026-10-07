#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
using vi = vector<ll>;
#define sz(x) ((ll)x.size())
#define all(x) begin(x),end(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    vi times(n);
    for (auto& x : times) cin >> x;

    vi ans;
    unordered_map<int,int> num_del;
    num_del.reserve(3e4);
    repp(i,1,n) {
        ll delta = times[i]-times[0];
        if (delta==0) continue;
        num_del.clear();

        rep(i,n) {
            if (num_del[times[i]]) {
                num_del[times[i]]--;
                continue;
            }
            num_del[times[i]+delta]++;
        }
        bool good = 1;
        for (auto [c, cnt] : num_del) good &= cnt==0;

        if (good) {
            ans.push_back(delta);
        }
    }

    ans.erase(unique(all(ans)),end(ans));
    cout << sz(ans) << '\n';
    for (auto x : ans) cout << x << ' ';
    return 0;
}