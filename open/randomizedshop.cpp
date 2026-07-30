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

    ll n, m;
    cin >> n >> m;

    priority_queue<p2> waiting;
    vector<p2> items(n);
    rep(i, n) {
        cin >> items[i].first;
    }
    rep(i, n) {
        cin >> items[i].second;
    }

    rep(i, n) {
        if (items[i].first >= items[i].second) continue;
        waiting.emplace(-items[i].first, items[i].second);
    }

    bool bought = false;

    auto transfer = [&]() {
        while (sz(waiting) && -waiting.top().first <= m) {
            m -= -waiting.top().first;
            m += waiting.top().second;
            waiting.pop();
        }
    };

    transfer();
    cout << m << '\n';
    return 0;
}
