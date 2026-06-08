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

    int n,k;
    cin >> n >> k;
    vvi res(4);
    rep(i,n) {
        int x;
        cin >> x;
        res[x%4].push_back(x);
    }

    rep(i,4) sort(all(res[i]));
    while (1) {
        if (res[k%4].empty()) break;
        int v = res[k%4].back();
        res[k%4].pop_back();
        k += v;
    }

    cout << k << '\n';


    return 0;
}
