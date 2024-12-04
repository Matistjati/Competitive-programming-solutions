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
    int n, k;
    cin >> n >> k;
    vi nums(n);
    rep(i, n) cin >> nums[i];


    map<int, vi> residues;
    rep(i, n) residues[nums[i] % k].push_back(nums[i]);

    int rem = 0;
    int ans = 0;
    repe(r, residues)
    {
        vi& res = r.second;
        if (sz(res) % 2 == 1)
        {
            if (n%2==1 && !rem)
            {
                rem = 1;
                if (sz(res) == 1) continue;

                sort(all(res));
                reverse(all(res));
                vi prefsum(sz(res));
                vi sufsum(sz(res));

                int acc = 0;
                for (int i = 0; i+1 < sz(res); i += 2)
                {
                    acc += (res[i] - res[i + 1]) / k;
                    prefsum[i] = acc;
                }

                acc = 0;
                for (int i = sz(res) - 1; i-1 >= 0; i -= 2)
                {
                    acc += (res[i-1] - res[i]) / k;
                    sufsum[i] = acc;
                }

                int b = inf;
                for (int i = 1; i + 3 < sz(res); i += 2)
                {
                    b = min(b, prefsum[i - 1] + sufsum[i + 3]);
                }
                b = min(b, sufsum[2]);
                b = min(b, prefsum[sz(res)-3]);
                ans += b;
                continue;
            }
            else
            {
                cout << "-1\n";
                return;
            }
        }
        sort(all(res));
        reverse(all(res));
        for (int i = 0; i < sz(res); i+=2)
        {
            ans += (res[i] - res[i + 1]) / k;
        }
    }
    cout << ans << "\n";
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
