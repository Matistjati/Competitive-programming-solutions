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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    map<char, int> ctoi;
    ctoi['A'] = 0;
    ctoi['C'] = 1;
    ctoi['T'] = 2;
    ctoi['G'] = 3;

    string s;
    cin >> s;
    s += "ACTG";

    vi seq(sz(s));
    vvi occ(4);
    rep(i, sz(s)) seq[i] = ctoi[s[i]], occ[seq[i]].push_back(i);

    vi dp(sz(s), inf);
    vi from(sz(s),-1);
    rep(i, 4) if (sz(occ[i])) dp[occ[i][0]] = 1;
    rep(i, sz(s)-4)
    {
        rep(j, 4)
        {
            int ind = *upper_bound(all(occ[j]), i);

            if (dp[i]+1<dp[ind])
            {
                dp[ind] = dp[i] + 1;
                from[ind] = i;
            }
        }
    }
    int best = sz(s)-4;
    rep(i, 4) if (dp[sz(s)-4 + i] < dp[best]) best = sz(s)-4+i;
    string ans;
    int i = best;
    while (i!=-1)
    {
        ans += s[i];
        i = from[i];
    }
    reverse(all(ans));
    cout << ans;

    return 0;
}
