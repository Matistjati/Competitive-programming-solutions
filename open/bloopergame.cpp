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

    ll n, l;
    long double p;
    cin >> n >> l >> p;

    vi sidelen(n);
    rep(i, n) cin >> sidelen[i];
    vector<long double> loglen(n);
    rep(i,n) loglen[i] = logl(sidelen[i]);

    vi coef(n);
    ll use=0;
    priority_queue<tuple<long double, int>> pq;
    auto push = [&](int i) {
        if (sidelen[i] == 1) return;
        pq.emplace(-(powl(p, coef[i]) * (-loglen[i])), i);
    };

    rep(i, n) push(i);
    while (use < l && sz(pq)) {
        auto [_, i] = pq.top();
        pq.pop();
        ll amount = max<ll>(1, (l-use)/n);
        coef[i]+=amount;
        use+=amount;
        push(i);
    }

    long double tot = 0;

    rep(i, n) {
        tot += powl(p, coef[i]) * (logl(1) - logl(sidelen[i]));
    }

    cout << fixed << setprecision(15) << exp(tot) << '\n';

    return 0;
}
