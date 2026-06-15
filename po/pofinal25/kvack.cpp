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

ll ask(ll x) {
    cout << "? " << x << endl;
    ll resp;
    cin >> resp;
    return resp;
}

set<ll> ducks;
void solve(ll lduck, ll rduck) { // find all ducks in [l,r]
    if (abs(lduck-rduck)<=1) return;
    ll a = (lduck+rduck+1)/2;
    ll resp = ask(a);
    bool resp_left = resp <= a;
    if (!ducks.count(resp)) {
        ducks.insert(resp);
        solve(lduck, resp);
        solve(resp, rduck);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    ll lduck = ask(-1e9);
    ll rduck = ask(2e9);

    if (lduck==rduck) {
        cout << "! 1\n" << lduck << endl;
    }
    else {
        ducks.insert(lduck);
        ducks.insert(rduck);
        solve(lduck,rduck);

        cout << "! " << sz(ducks) << '\n';
        repe(u, ducks) cout << u << ' ';
        cout << endl;
    }

    return 0;
}
