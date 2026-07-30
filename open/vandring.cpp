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

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int r;
    cin >> r;
    vvi grid(r, vi(r));
    rep(i, r) rep(j, r) cin >> grid[i][j];

    bool good = 1;
    vector<vector<p2>> cnt(r * r);
    rep(i, r) rep(j, r) cnt[grid[i][j]].emplace_back(i,j);

    int largest = 0;
    rep(i, sz(cnt)) largest = max<int>(largest, sz(cnt[i]));

    if (largest <= r)
    {
        rep(v, sz(cnt))
        {
            vector<p2> occs = cnt[v];
            sort(all(occs));

            int cutoffright = r;
            repe(p, occs)
            {
                if (p.second >= cutoffright) good = 0;
                cutoffright = p.second;
            }
        }
    }
    else good = 0;


    cout << good << "\n";

    return 0;
}
