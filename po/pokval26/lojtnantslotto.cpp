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

const int maxval = 5;
const int window_size = 20;
int brute(ll ind, ll cap_left, ll sum, vi& howfar, vvi& occs)
{
    if (ind == maxval + 1)
    {
        return 0;
    }
    
    ll ret = brute(ind + 1, cap_left, sum, howfar, occs);
    repp(i, max(0LL, howfar[ind] - window_size), min(sz(occs[ind]), howfar[ind] + window_size))
    {
        if (occs[ind][i] > cap_left) continue;
        ret = max(ret, (i+1) * ind + brute(ind + 1, cap_left - occs[ind][i], sum+ind*i, howfar, occs));
    }

    return ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);


    int n, t;
    cin >> n >> t;
    vector<p2> castles(n);
    repe(c, castles) cin >> c.first >> c.second;

    vvi occs(maxval + 1);
    for (auto [profit, weight] : castles) occs[profit].push_back(weight);
    repe(o, occs) sort(all(o));
    vvi occs_pref = occs;
    rep(i, maxval + 1) repp(j, 1, sz(occs_pref[i])) occs_pref[i][j] += occs_pref[i][j - 1];

    vi howfar(maxval + 1);
    int cand_ans = 0;
    int cand_t = 0;
    while (true)
    {
        double bestratio = 0;
        int bestw = 0;
        rep(i, maxval + 1)
        {
            if (howfar[i] == sz(occs[i])) continue;
            if (occs[i][howfar[i]] + cand_t > t) continue;
            double r = (i + 0.) / occs[i][howfar[i]];
            if (r > bestratio)
            {
                bestratio = r;
                bestw = i;
            }
        }
        if (bestw == 0) break;
        cand_ans+=bestw;
        cand_t += occs[bestw][howfar[bestw]++];
    }

    cout << brute(0, t, 0, howfar, occs_pref) << '\n';

    return 0;
}
