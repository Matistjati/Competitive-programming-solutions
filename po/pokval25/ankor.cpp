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

    int n;
    cin >> n;

    vector<p2> ducks(n*2);
    rep(i, n*2) cin >> ducks[i].first >> ducks[i].second;
    double k = 3.14159265358979;
    double lo = -1e7;
    double hi = 1e7;
    rep(i, 100)
    {
        double mid = (lo + hi) / 2;
        int num_above = 0;
        repe(d, ducks) num_above += d.second > (d.first * k + mid);
        if (num_above <= n) hi = mid;
        else lo = mid;
    }
    cout << fixed << setprecision(10) << k << " " << hi+1e-8 << endl;

    return 0;
}
