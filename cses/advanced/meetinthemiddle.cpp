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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int n, t;
    cin >> n >> t;
    vi nums(n);
    rep(i, n) cin >> nums[i];
    if (n==1)
    {
        cout << (nums[0] == t);
        return 0;
    }

    int split = n / 2+1;
    vi h1;
    rep(i, split) h1.push_back(nums[i]);
    vi h2;
    repp(i, split, n) h2.push_back(nums[i]);

    unordered_map<int, int> dist;
    dist.reserve(1 << 21);

    rep(mask, 1 << split)
    {
        int s = 0;
        rep(i, split) if (mask & (1 << i)) s += h1[i];
        dist[s]++;
    }

    int ans = 0;
    rep(mask, 1 << (n - split))
    {
        int s = 0;
        rep(i, sz(h2)) if (mask & (1 << i)) s += h2[i];
        auto it = dist.find(t-s);
        if (it!=dist.end()) ans += it->second;
    }
    cout << ans;

    return 0;
}
