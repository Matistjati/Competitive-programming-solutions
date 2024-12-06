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

    int n, p;
    cin >> n >> p;
    int req = (n * p + 99) / 100;

    vector<p2> pts(n);
    rep(i, n) cin >> pts[i].first >> pts[i].second;

    map<int, int> vertical;
    rep(i, n) vertical[pts[i].first]++;
    repe(v, vertical)
    {
        if (v.second>=req)
        {
            cout << "possible";
            return 0;
        }
    }

    mt19937 rng(10);
    uniform_int_distribution<int> dist(0, n - 1);
    rep(i, 1000)
    {
        int a = dist(rng);
        int b;
        while ((b=dist(rng))==a){}
        if (pts[a].first == pts[b].first)
        {
            i--;
            continue;
        }

        long double k = (pts[a].second - pts[b].second) / (long double)(pts[a].first - pts[b].first);
        
        long double m = pts[a].second - pts[a].first * k;

        int cnt = 0;
        rep(i, n)
        {
            cnt += abs(pts[i].first * k + m - pts[i].second) < 1e-10;
        }
        if (cnt >= req)
        {
            cout << "possible";
            return 0;
        }
    }
    cout << "impossible";

    return 0;
}
