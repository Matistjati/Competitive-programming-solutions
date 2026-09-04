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

    int r,c,k,n;
    cin >> r >> c >> k >> n;
    vector<int> cols(k);
    rep(i, k) cin >> cols[i];
    vector<p2> obstacles(n);
    rep(i, n) cin >> obstacles[i].first >> obstacles[i].second;
    sort(all(obstacles));
    map<int, set<int>> obstacle_cols;
    for (auto [r,c] : obstacles) {
        obstacle_cols[c].insert(r);
    }

    set<p2> seen;
    queue<p2> q;
    auto try_push = [&](int row, int col) {
        if (row < 0 || col < 0 || col >= c) return;
        if (binary_search(all(obstacles), p2({row, col}))) return;
        if (seen.count({row, col})) return;
        seen.insert({row, col});
        q.push({row, col});
    };

    for (auto col : cols) {
        seen.insert({r, col});
        q.push({r, col});
    }

    set<int> ans_cols;
    while (sz(q)) {
        auto [r, c] = q.front();
        q.pop();

        if (binary_search(all(obstacles), p2({r-1, c}))) {
            try_push(r, c+1);
            try_push(r, c-1);
        }
        else {
            auto it = obstacle_cols[c].lower_bound(r);
            if (it == begin(obstacle_cols[c])) {
                ans_cols.insert(c);
            }
            else {
                try_push(*prev(it)+1, c);
            }
        }
    }

    cout << sz(ans_cols) << '\n';

    return 0;
}
