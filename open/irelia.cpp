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

    int n, l;
    cin >> n >> l;
    vi a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];

    using ld = long double;
    auto solve = [&](ld mid) {
        auto at = [&](int i) {
            return a[i] - mid * b[i];
        };
        ld best_prev = inf;
        ld ret = -inf;
        ld prefsum = 0;
        queue<pair<int, ld>> waiting;
        waiting.emplace(-1, 0);
        rep(i, n) {
            prefsum += at(i);
            waiting.emplace(i, prefsum);
            // best suffix ending at i
            while (sz(waiting) && i - waiting.front().first >= l) {
                best_prev = min(best_prev, waiting.front().second);
                waiting.pop();
            }
            ret = max(ret, prefsum - best_prev);
        }

        return ret >= 0;
    };

    ld lo = 0;
    ld hi = 1e15;
    rep(i, 100) {
        ld mid = (lo + hi) / 2;
        if (solve(mid)) lo = mid;
        else hi = mid;
    }

    cout << fixed << setprecision(15) << lo << '\n';


    return 0;
}
