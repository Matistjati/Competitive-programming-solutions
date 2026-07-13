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

bool evaluate(vector<tuple<int,int,int>>& trees, int time, int t) {
    ll height = -t;

    for (auto [h, dh, max_age] : trees) {
        height += h + dh * (ll)min(time, max_age);
        if (height >= 0) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, s;
    cin >> n >> s;
    vector<tuple<int,int,int>> trees;
    rep(i, n) {
        int l, v, t;
        cin >> l >> v >> t;
        trees.emplace_back(l, v, t);
    }

    int lo = -1;
    int hi = ll(1e9) + 10;

    while (lo+1<hi) {
        int mid = (lo + hi) / 2;
        bool works = evaluate(trees, mid, s);
        if (works) hi = mid;
        else lo = mid;
    }

    cout << hi << '\n';
    return 0;
}
