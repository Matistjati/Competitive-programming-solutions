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
    int x = 1;
    vi ans;
    while (x <= n) {
        ans.push_back(x);
        x *= 2;
    }
    cout << sz(ans) << '\n';
    repe(u, ans) cout << u << ' ';
    cout << '\n';

    return 0;
}
