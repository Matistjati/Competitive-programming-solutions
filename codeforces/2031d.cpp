#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


void solve()
{
    int n;
    cin >> n;
    vi heights(n);
    rep(i, n) cin >> heights[i];
    int lind = 0;
    
    vi largeleft(n);
    vi smolright(n);

    vi localmax;
    localmax.push_back(0);
    rep(i, n)
    {
        if (heights[i]>heights[lind])
        {
            lind = i;
            localmax.push_back(i);
        }
        largeleft[i] = lind;
    }
    
    int smolind = n - 1;
    for (int i = n-1; i >= 0; i--)
    {
        smolright[i] = smolind;
        if (heights[i] < heights[smolind])
        {
            smolind = i;
        }
    }
    vi ans(n);
    rep(i, sz(localmax)) ans[localmax[i]] = heights[localmax[i]];

    for (int i = sz(localmax) - 1; i > 0; i--)
    {
        int ind = localmax[i];
        int pind = localmax[i - 1];
        int r = smolright[ind];
        if (heights[r]<heights[pind])
        {
            ans[pind] = ans[ind];
        }
    }

    rep(i, n)
    {
        cout << ans[largeleft[i]] << " ";
    }

    cout << "\n";
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
