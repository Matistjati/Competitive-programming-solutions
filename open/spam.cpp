#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int k;
    cin >> k;
    string s;
    cin >> s;

    auto solve = [s, k](double mid)
    {
        pair<double, int> bestpref = { 0,1 };

        pair<double, pair<int, int>> ret;
        ret.first = -inf;
        ret.second = { 1,1 };
        double pref = 0;
        vector<double> dp(sz(s));
        rep(i, sz(s))
        {
            dp[i] = pref;
            pref += s[i]-'0'-mid;
            

            if (i+1>=k)
            {
                if (dp[i-k+1]<bestpref.first)
                {
                    bestpref = { dp[i - k+1], i - k+2 };
                }
                if (pref-bestpref.first>ret.first)
                {
                    ret = make_pair(pref - bestpref.first, make_pair(bestpref.second, i-bestpref.second+2));
                }
            }
        }
        return ret;
    };

    double lo = 0;
    double hi = 2;
    rep(i, 60)
    {
        double mid = (lo + hi) / 2;
        if (solve(mid).first>=0)
        {
            lo = mid;
        }
        else
        {
            hi = mid;
        }
    }
    //cout << hi << "\n";
    cout << solve(lo).second.first << " " << solve(lo).second.second;

    return 0;
}
