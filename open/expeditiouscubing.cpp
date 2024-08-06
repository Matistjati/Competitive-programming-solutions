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

    double a_, b_, c_, d_;
    cin >> a_ >> b_ >> c_ >> d_;
    double t_;
    cin >> t_;

    int a = round(a_ * 100);
    int b = round(b_ * 100);
    int c = round(c_ * 100);
    int d = round(d_ * 100);
    int t = round(t_ * 100);

    vi nums = { a,b,c,d };
    sort(all(nums));
    // check impossible
    int bestavg = nums[1] + nums[2] + nums[3];
    bestavg = min(bestavg, nums[0] + nums[1] + nums[2]);
    if (bestavg>t*3)
    {
        cout << "impossible";
        return 0;
    }

    int avgbad = nums[1] + nums[2] + nums[3];
    if (avgbad <= t * 3)
    {
        cout << "infinite";
        return 0;
    }

    for (int i = int(1e5); i >= 0; i--)
    {
        vi num = { a,b,c,d,i };
        sort(all(num));
        int avg = num[1] + num[2] + num[3];
        if (avg<=t*3)
        {
            cout << fixed << setprecision(2) << (i / 100.);
            return 0;
        }
    }

    return 0;
}
