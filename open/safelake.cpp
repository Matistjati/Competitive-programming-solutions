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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> grid(n);
        rep(i, n) cin >> grid[i];

        vvi vis(n, vi(n));
        vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
        function<void(p2)> prop_good;

        vvi isgood(n, vi(n));

        auto is_outside = [&](p2 pos, p2 dir) {
            pos = { pos.first + dir.first,pos.second + dir.second };
            return (pos.first < 0 || pos.second < 0 || pos.first >= n || pos.second >= n);
        };

        map<char, p2> rdirs;
        rdirs['L'] = { 0,-1 };
        rdirs['R'] = { 0,1 };
        rdirs['U'] = { -1,0 };
        rdirs['D'] = { 1,0 };

        auto revdir = [](p2 p) {
            return p2(-p.first, -p.second);
        };

        auto rev = [&](p2 p) {
            for (auto [c, d] : rdirs) {
                if (p == d) return c;
            }
            assert(0);
        };

        prop_good = [&](p2 p) {
            if (isgood[p.first][p.second]) return;
            isgood[p.first][p.second] = 1;
            assert(grid[p.first][p.second] != '?');
            repe(dir, dirs) {
                if (is_outside(p, dir)) continue;
                p2 np = { p.first + dir.first,p.second + dir.second };
                if (grid[np.first][np.second]=='?') {
                    if (dir == rdirs[grid[p.first][p.second]]) continue; // cant help
                    grid[np.first][np.second] = rev(revdir(dir));
                    prop_good(np);
                }
                else {
                    p2 dir = rdirs[grid[np.first][np.second]];
                    p2 npp = { np.first + dir.first,np.second + dir.second };
                    if (npp == p) {
                        prop_good(np);
                    }
                }
            }
        };

        if (grid[0][0] == '?') grid[0][0] = 'L';
        rep(i, n) rep(j, n) {
            if (grid[i][j] == '?') {
                repe(dir, dirs) {
                    if (is_outside(p2(i, j), dir)) {
                        grid[i][j] = rev(dir);
                        prop_good(p2(i, j));
                    }
                }
            }
            else if (is_outside(p2(i, j), rdirs[grid[i][j]])) {
                prop_good(p2(i, j));
            }
        }

        int totgood = 0;
        rep(i,n) totgood += accumulate(all(isgood[i]),0);

        if (totgood<n*n) {
            cout << "-1\n";
        }
        else {
            rep(i, n) cout << grid[i] << '\n';
        }
    }

    return 0;
}
