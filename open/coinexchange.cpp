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

int solve(int a, int b, int d, int e, int x, bool greedy)
{

    int k = e / 3;
    e -= k * 3;
    d += k * 2;
    k = d / 2;
    k = min(k, x);
    d -= k * 2;
    x -= k;
    b += k * 3;

    auto calc_am = [&](int b)
        {
            int e2 = e + b;

            int d2 = e2 / 3 * 2 + d;
            k = d2 / 2;
            return k;
        };

    while (x)
    {
        int bb = b / 3 * 4;
        if (bb == 0) break;
        if (calc_am(bb) <= x)
        {
            e += b / 3 * 4;
            b -= b / 3 * 3;
            int k = e / 3;
            e -= k * 3;
            d += k * 2;
            k = d / 2;
            k = min(k, x);
            d -= k * 2;
            x -= k;
            b += k * 3;
        }
        else
        {
            int lo = -1;
            int hi = b / 3;
            while (lo+1<hi)
            {
                int mid = (lo + hi) / 2;
                if (calc_am(mid*4) <= x) lo = mid;
                else hi = mid;
            }
            if (greedy) lo = hi;
            b -= lo * 3;
            e += 4 * lo;
            int k = e / 3;
            e -= k * 3;
            d += k * 2;
            k = d / 2;
            k = min(k, x);
            d -= k * 2;
            x -= k;
            b += k * 3;
            break;
        }
    }

    int ret = a / 5 + b/3;
    return ret;
}

signed main()
{
    fast();

    int a, b, c, d, e, x;
    cin >> a >> b >> c >> d >> e >> x;


    int ans = 0;
    rep(i, min(100LL, a/3+1))
    {
        ans = max(ans, solve(a - i * 3, b + i, d, e, x, 1));
        ans = max(ans, solve(a - i * 3, b + i, d, e, x, 0));
        //break;
    }

    cout << ans + c;

    return 0;
}
