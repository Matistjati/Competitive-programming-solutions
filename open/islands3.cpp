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
    vector<string> grid(r);
    rep(i,r) cin >> grid[i];

    vector<p2> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    int ans = 0;
    rep(i,r) rep(j,c) {
        if (grid[i][j]=='W'||grid[i][j]=='C') continue;
        ans++;
        vector<p2> st = {{i,j}};
        while (sz(st)) {
            auto [i,j] = st.back();
            st.pop_back();
            if (grid[i][j]=='W') continue;
            grid[i][j]='W';
            for (auto [di,dj] : dirs) {
                p2 np = {i+di,j+dj};
                if (np.first<0||np.second<0||np.first>=r||np.second>=c) continue;
                st.push_back(np);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
