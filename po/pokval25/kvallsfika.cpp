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

    int n, p, k;
    cin >> n >> p >> k;
    vector<p2> items(n);
    rep(i, n) cin >> items[i].first;
    rep(i, n) cin >> items[i].second;
    sort(all(items));
    map<int, int> taken;
    int ans = 0;

    rep(i, n)
    {
        int c, t;
        tie(c, t) = items[i];
        if (p >= c && taken[t] + 1 <= k)
        {
            ans++;
            p -= c;
            taken[t]++;
        }
    }

    cout << ans << endl;

    return 0;
}
