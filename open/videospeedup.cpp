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

    int n, p, k;
    cin >> n >> p >> k;
    
    double start = 0;
    double speed = 1;
    double time = 0;
    rep(i, n)
    {
        int t;
        cin >> t;
        time += (t - start) * (1+double(p)*i/100);
        start = t;
    }
    time += (k - start) * (1 + double(n)*p / 100);
    cout << fixed << setprecision(15) << time;

    return 0;
}
