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

int ans = inf;
void rec(int i, int g, int taken, vi& nums)
{
    if (taken >= ans) return;
    if (g == 1)
    {
        ans = min(ans, taken);
        return;
    }
    if (i == sz(nums)) return;

    rep(t, 10)
    {
        if (taken + t >= ans) break;
        rec(i + 1, gcd(g, nums[i] + t), taken + t, nums);
    }
}

signed main()
{
    fast();

    int n;
    cin >> n;
    vi nums(n);
    repe(v, nums) cin >> v;

    mt19937 rng(10);
    shuffle(all(nums), rng);
    rep(i, 10) rec(1, nums[0] + i, i, nums);
    cout << ans;

    return 0;
}
