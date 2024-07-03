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

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vi nums(n);
        rep(i, n) cin >> nums[i];

        vector<pair<int, p2>> dp;
        rep(i, n)
        {
            vector<pair<int, p2>> to_insert;
            repe(u, dp)
            {
                int c, j, k;
                c = u.first;
                j = u.second.first;
                k = u.second.second;
                to_insert.emplace_back(c, p2(j, k));
                if (nums[i] == j || nums[i] == k) continue;

                p2 np = p2(nums[i], j);
                to_insert.emplace_back(c + 1, np);
            }
            to_insert.emplace_back(1, p2(nums[i], -1));
            sort(to_insert.rbegin(), to_insert.rend());

            set<int> seen;
            vector<pair<int, p2>> new_dp;

            repe(u, to_insert)
            {
                if (sz(new_dp) > 10) break;
                int ind = u.second.first * int(2e9) + u.second.second;
                if (seen.find(ind) != seen.end()) continue;
                seen.insert(ind);
                new_dp.emplace_back(u);
            }
            dp = new_dp;
        }
        int ans = 0;
        repe(u, dp)
        {
            ans = max(ans, u.first);
        }
        cout << ans << "\n";
    }

    return 0;
}
