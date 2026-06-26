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
    vector<p2> x(n);
    vector<p2> y(n);
    rep(i,n) {
        int a,b,w;
        cin >> a >> b >> w;
        x[i] = {a,w};
        y[i] = {b,w};
    }

    auto solve = [](vector<p2>& coords) {
        sort(all(coords));
        
        repp(i,1,sz(coords)) {
            coords[i].second+=coords[i-1].second;
        }
        ll tot = coords.back().second;
        for (auto [_,w] : coords) {
            if (w*2>=tot) return _;
        }
    };

    cout << solve(x) << ' ' << solve(y) << '\n';

    return 0;
}
