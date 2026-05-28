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

    int n,m;
    cin >> n >> m;
    string ans(n,'?');
    rep(i,m) {
        int p;
        cin >> p;
        string s;
        cin >> s;
        rep(o,sz(s)) {
            if (ans[o+p-1] != '?' && ans[o+p-1] != s[o]) {
                cout << "Villa\n";
                return 0;
            }
            ans[o+p-1] = s[o];
        }
    }

    cout << ans << '\n';


    return 0;
}

