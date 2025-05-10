#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }


double solvespam(int k, string& s)
{
    vector<double> dp(sz(s));

    auto solve = [s, k, &dp](double mid)
        {
            double bestpref = 0;

            double ret = -inf;
            double pref = 0;
            rep(i, sz(s)) dp[i] = 0;
            rep(i, sz(s))
            {
                dp[i] = pref;
                pref += s[i] - '0' - mid;


                if (i + 1 >= k)
                {
                    if (dp[i - k + 1] < bestpref)
                    {
                        bestpref = dp[i - k + 1];
                    }
                    if (pref - bestpref > ret)
                    {
                        ret = pref - bestpref;
                    }
                }
            }
            return ret;
        };

    double lo = 0;
    double hi = 2;
    rep(i, 25)
    {
        double mid = (lo + hi) / 2;
        if (solve(mid) >= 0)
        {
            lo = mid;
        }
        else
        {
            hi = mid;
        }
    }
    //cout << hi << "\n";
    return lo;

}

signed main()
{
    fast();

    int n, k;
    cin >> n >> k;
    vi nums(n);
    repe(v, nums) cin >> v;
    set<int> uniq(all(nums));

    map<int, int> compress;
    repe(v, uniq) compress[v] = sz(compress);
    repe(v, nums) v = compress[v];

    map<int, int> occ;
    repe(v, nums)occ[v]++;
    vector<p2>daasd;
    repe(u, occ) daasd.emplace_back(u.second, u.first);
    sort(all(daasd));
    reverse(all(daasd));

    double ans = 0;

    string s(n, '0');
    map<int, vi> occs;
    rep(i, n) occs[nums[i]].push_back(i);
    repe(o, daasd)
    {
        if (o.first > 1500)
        {
            rep(i, n)
            {
                if (o.second == nums[i]) s[i] = '1';
                else s[i] = '0';
            }
            ans = max(ans, solvespam(k, s));
        }
        else
        {
            vi& pos = occs[o.second];
            int s = o.first;
            rep(i, s)
            {
                repp(j, i, s)
                {
                    int cnt = j - i + 1;
                    int len = max(k, pos[j] - pos[i] + 1);
                    ans = max(ans, double(cnt) / len);
                }
            }
        }
    }

    cout << fixed << setprecision(15) << ans;

    return 0;
}
