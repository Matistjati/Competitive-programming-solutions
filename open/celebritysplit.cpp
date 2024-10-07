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

void rec(int i, int asum, int bsum, int csum, vi& nums, unordered_map<int,int>& bestdeal)
{
    if (i==sz(nums))
    {
        if (bestdeal.find(bsum - asum) == bestdeal.end()) bestdeal[bsum - asum] = inf;
        bestdeal[bsum - asum] = min(bestdeal[bsum - asum], csum);
        return;
    }
    rec(i + 1, asum, bsum, csum+nums[i], nums, bestdeal);
    rec(i + 1, asum+nums[i], bsum, csum, nums, bestdeal);
    rec(i + 1, asum, bsum+nums[i], csum, nums, bestdeal);
}
int rec2(int i, int asum, int bsum, int csum, vi& nums, unordered_map<int,int>& bestdeal)
{
    if (i==sz(nums))
    {
        if (bestdeal.find(asum-bsum)!=bestdeal.end())
        {
            return csum + bestdeal[asum - bsum];
        }
        return inf;
    }
    int ret = inf;
    ret = min(ret, rec2(i + 1, asum, bsum, csum+nums[i], nums, bestdeal));
    ret = min(ret, rec2(i + 1, asum+nums[i], bsum, csum, nums, bestdeal));
    ret = min(ret, rec2(i + 1, asum, bsum+nums[i], csum, nums, bestdeal));
    return ret;
}

signed main()
{
    fast();

    int n;
    while (cin >> n && n)
    {
        vi nums(n);
        rep(i, n) cin >> nums[i];
        if (n==1)
        {
            cout << nums[0] << "\n";
            continue;
        }

        int split = n / 2;
        vi h1;
        rep(i, split + 1) h1.push_back(nums[i]);
        unordered_map<int, int> bestdeal;
        bestdeal.reserve((int)pow(3, sz(h1))*2);
        rec(0, 0, 0, 0, h1, bestdeal);
        vi h2;
        repp(i, split + 1, n) h2.push_back(nums[i]);


        cout << rec2(0,0,0,0,h2,bestdeal) << "\n";
    }


    return 0;
}
