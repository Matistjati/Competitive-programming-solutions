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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();
    
    int n, x;
    cin >> n >> x;
    
    vi nums;
    int ans = 0;
    rep(i, n)
    {
        int l;
        cin >> l;
        ans = max(ans, l);
        if (l <= x) nums.push_back(l);
    }
    if (sz(nums)==0)
    {
        cout << ans;
        return 0;
    }
    if (sz(nums)==1)
    {
        cout << max(ans,nums[0]);
        return 0;
    }
    if (sz(nums)==2)
    {
        cout << max(max(ans,nums[0]), nums[1]);
        return 0;
    }
    if (sz(nums)<=4)
    {
        cout << max(max(ans,x+1), *max_element(nums.begin(), nums.end()));
        return 0;
    }
    sort(nums.rbegin(),nums.rend());
    int r = min(sz(nums), 4LL);
    rep(i, r) ans = max(ans, nums.back()), nums.pop_back();
    n = sz(nums);
    rep(i, n)nums[i] = x + 1 - nums[i];
    int tt = accumulate(nums.begin(),nums.end(),0LL);
    int t = tt/2;

    int s = 0;
    rep(i, n)
    {
        if (s+nums[i]<=t)
        {
            s += nums[i];
            nums[i] = -nums[i];
        }
    }

    mt19937 rng;
    shuffle(nums.begin(), nums.end(), rng);

    const int k = int(2e4);
    bitset<k> bset;
    bset[k/2] = 1;
    repe(num, nums)
    {
        if (num > 0) bset |= bset << num;
        else bset |= bset >> (-num);
    }

    int d = t - s;
    int best = inf;
    for (int i = k/2; i < k; i++)
    {
        if (bset[i])
        {
            int v = s+i-k/2;
            best = min(best, max(v,tt-v));
        }
    }
    cout << max(ans, x + 1 + best);

    return 0;
}

