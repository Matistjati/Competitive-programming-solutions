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

signed main()
{
    fast();

    int n;
    cin >> n;
    vi nums(n);
    rep(i, n) cin >> nums[i];
    sort(all(nums));
    reverse(all(nums));
    int ans = 0;
    for (int i = 0; i < n; i+=3)
    {
        ans += nums[i];
        if (i + 1 < n) ans += nums[i + 1];
    }
    cout << ans;

    return 0;
}
