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

    vector<string> grid(8);
    rep(i,8) cin >> grid[i];

    auto has = [&](char c) {
        rep(i,8) rep(j,8) if (grid[i][j]==c) return true;
        return false;
    };

    if (has('K') && has('k')) cout << "Spennan er i hámarki!\n";
    else if (has('k')) cout << "Hvítur\n";
    else cout << "Svartur\n";

    return 0;
}
