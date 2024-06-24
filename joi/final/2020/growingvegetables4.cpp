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

    int n;
    cin >> n;
    vi nums(n);
    rep(i, n) cin >> nums[i];
    vi diff(n - 1);
    rep(i, sz(diff)) diff[i] = nums[i + 1] - nums[i];

    vi costl(n - 1);
    vi costr(n - 1);

    rep(i, n - 1)
    {
        int c = i > 0 ? costl[i - 1] : 0;
        if (diff[i] <= 0) c += -diff[i] + 1;
        costl[i] = c;
    }
    
    for (int i = n - 2; i >= 0; i--)
    {
        int c = i < n-2 ? costr[i + 1] : 0;
        if (diff[i] >= 0) c += diff[i] + 1;
        costr[i] = c;
    }

    int ans = inf;
    rep(i, n-1)
    {
        int l = 0;
        int r = 0;
        if (i) l = costl[i - 1];
        if (i + 1 < sz(diff)) r = costr[i + 1];
        int t = max(l, r);
        if (l == r && diff[i] == 0) t++;
        ans = min(ans, t);
    }
    cout << ans;

    return 0;
}
