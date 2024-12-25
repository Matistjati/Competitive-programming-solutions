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

double gcDist(double pLa, double pLo, double qLa, double qLo, double r) {
    pLa *= 3.14159265358979323846264 / 180;
    pLo *= 3.14159265358979323846264 / 180;  // degree to radian
    qLa *= 3.14159265358979323846264 / 180;
    qLo *= 3.14159265358979323846264 / 180;
    return r * acos(cos(pLa) * cos(pLo) * cos(qLa) * cos(qLo) +
        cos(pLa) * sin(pLo) * cos(qLa) * sin(qLo) + sin(pLa) * sin(qLa));
}

signed main()
{
    fast();

    int n;
    while (cin >> n)
    {
        vector<pair<double, double>> coords(n);
        rep(i, n) cin >> coords[i].first >> coords[i].second;

        auto dist = [&](int a, int b)
            {
                return gcDist(coords[a].first, coords[a].second, coords[b].first, coords[b].second, 1);
            };

        int best = 0;
        auto maxdist = [&](int ex)
            {
                double ret = 0;
                rep(i, n)
                {
                    if (i == ex) continue;
                    ret = max(ret, dist(i,ex));
                }
                return ret;
            };
        repp(i, 1, n)
        {
            double bd = maxdist(best);
            double di = maxdist(i);
            if (di <= bd || abs(bd - di) < 1e-9)
            {
                best = i;
            }
        }
        cout << fixed << setprecision(2) << coords[best].first << " " << coords[best].second << "\n";
    }

    return 0;
}
