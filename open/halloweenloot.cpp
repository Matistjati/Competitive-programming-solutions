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

constexpr int bsz = int(100 * 100 * 2 + 10);
int min_abs_diff(vector<p2> nums, int offset)
{
    bitset<bsz> bset;
    int mid = 100 * 100 + 1;
    bset[mid+offset] = 1;

    repe(num, nums)
    {
        num.second = -num.second;
        bitset<bsz> l(bset);
        if (num.first >= 0) l <<= num.first;
        else l >>= -num.first;
        bitset<bsz> r(bset);
        if (num.second >= 0) r <<= num.second;
        else r >>= -num.second;

        bset = l | r;
    }

    int ans = inf;
    rep(i, bsz)
    {
        if (bset[i]) ans = min(ans, abs(i - mid));
    }
    return ans;
}

signed main()
{
    fast();

    int n;
    cin >> n;
    vector<p2> nums(n);
    rep(i, n) cin >> nums[i].first;
    rep(i, n) cin >> nums[i].second;

    int best = min_abs_diff(nums, 0);
    
    int sum = 0;
    string ans = "";
    while (sz(nums))
    {
        p2 p = nums[0];
        nums.erase(nums.begin());
        if (min_abs_diff(nums, sum+p.first)==best)
        {
            ans += "A";
            sum += p.first;
        }
        else
        {
            sum -= p.second;
            ans += "B";
        }
    }
    cout << ans;


    return 0;
}
