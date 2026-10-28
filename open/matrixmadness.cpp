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
    
    int r,c;
    cin >> r >> c;

    vvi mat(r,vi(c));
    rep(i,r) rep(j,c) cin >> mat[i][j];

    rep(i,r) rep(j,c) {
        rep(k, r) rep(l,c) {
            if (i==k && j==l) continue;
            if (mat[i][j]==mat[k][l] && abs(i-k)+abs(j-l) <= mat[i][j]) {
                cout << "INVALID\n";
                return 0;
            }
        }
    }
    
    cout << "VALID\n";

    return 0;
}
