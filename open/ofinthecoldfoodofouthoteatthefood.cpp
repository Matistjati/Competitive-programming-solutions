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

signed main()
{
    fast();

    int t, h;
    cin >> t >> h;

    auto cookamount = [&](double x)
        {
            if (x > h)
            {
                return h / 2. + x-h;
            }
            else return x*x/(2.0*h);
        };

    double lo = 0;
    double hi = 1e18;
    rep(i,200)
    {
        double mid = (lo + hi) / 2;
        if (cookamount(mid) >= t) hi = mid;
        else lo = mid;
    }
    cout << fixed << setprecision(15) << hi;

    return 0;
}
