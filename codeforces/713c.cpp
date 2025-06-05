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

signed main()
{
    fast();

    int n;
    cin >> n;
    vi nums(n);
    repe(v, nums) cin >> v;
    rep(i, n) nums[i] -= i;

    map<int, int> fn;

    int k = -1;
    int m = nums[0];
    fn[nums[0]] = 2;

    int totalslope = 1;

    auto pop = [&]()
        {
            auto it = prev(end(fn));
            p2 v = *it;
            fn.erase(it);
            if (v.second > totalslope)
            {
                v.second -= totalslope;
                fn.insert(v);
                totalslope = 0;
            }
            else
            {
                totalslope -= v.second;
            }
        };

    repp(i, 1, n)
    {
        while (totalslope>0)
        {
            pop();
        }


        k--;
        totalslope--;
        fn[nums[i]] += 2;
        totalslope += 2;
        m += nums[i];
    }

    while (totalslope > 0)
    {
        pop();
    }

    int prev = begin(fn)->first;
    int ans = prev * k + m;
    k += begin(fn)->second;
    auto it = next(begin(fn));
    while (it!=end(fn))
    {
        int delta = it->first - prev;
        ans += k * delta;
        k += it->second;
        prev = it->first;
        it = next(it);
    }

    cout << ans;

    return 0;
}
