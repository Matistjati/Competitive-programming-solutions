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



signed main()
{
    fast();

    int n, l;
    cin >> n >> l;
    vi run(n);
    vi bike(n);
    rep(i, n) cin >> run[i] >> bike[i];

    double lo = 0;
    double hi = int(1e8);

    rep(i, 100)
    {
        double mid = (lo + hi) / 2;

        double bike_distance = 0;
        rep(i, n)
        {
            if (mid*run[i] >= l)
            {
                continue;
            }
            if (bike[i] <= run[i])
            {
                bike_distance += int(1e8);
                break;
            }
            double save_needed = l - mid * run[i];
            double dspeed = bike[i] - run[i];

            bike_distance += bike[i] * save_needed / dspeed;
        }

        if (bike_distance <= l)
        {
            hi = mid;
        }
        else lo = mid;
    }
    cout << lo;

    return 0;
}
