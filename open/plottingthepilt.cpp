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

    int r,c,d;
    cin >> r >> c >> d;
    vector<p2> dirs = {{0,1},{1,0},{0,-1},{-1,0}};

    vvi grid(r,vi(c));
    rep(i,r) rep(j,c) cin >> grid[i][j];

    auto k = [&](int i, int j) {
        return grid[i][j]/d;
    };

    auto m = [&](int i, int j) {
        ll ret = INT_MAX;
        for (auto [di,dj] : dirs) {
            p2 np = {i+di,j+dj};
            if (np.first<0||np.second<0||np.first>=r||np.second>=c) continue;
            ret = min(ret, k(np.first,np.second));
        }
        return ret;
    };

    rep(i,r) {
        rep(j,c) {
            int mym = m(i,j);

            if (k(i,j) <= mym) cout << " ";
            else if (k(i,j)==mym+1) cout << "+";
            else if (k(i,j)==mym+2) cout << "X";
            else cout << "#";
        }
        cout << '\n';
    }

    return 0;
}
