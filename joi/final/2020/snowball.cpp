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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    vi balls(n);
    rep(i, n) cin >> balls[i];
    vi delta(q);
    rep(i, q) cin >> delta[i];
    n += 2;
    balls.insert(balls.begin(), - inf);
    balls.push_back(inf);


    bool posfirst = delta[0] > 0;
    vi pref(delta);
    repp(i, 1, q) pref[i] += pref[i - 1];
    vi prefmax(pref);
    vi prefmin(pref);
    prefmax.insert(prefmax.begin(), 0LL);
    prefmin.insert(prefmin.begin(), 0LL);
    q++;
    repp(i, 1, q) prefmax[i] = max(prefmax[i], prefmax[i - 1]);
    repp(i, 1, q) prefmin[i] = min(prefmin[i], prefmin[i - 1]);
    delta.insert(delta.begin(), 0LL);

    repp(i, 1, n - 1)
    {
        int l = 0;
        int lo = -1;
        int hi = sz(prefmin);
        while (lo+1<hi)
        {
            int mid = (lo + hi) / 2;
            int mlo = balls[i] + prefmin[mid];
            int phi = balls[i - 1] + prefmax[mid];
            if (phi >= mlo) hi = mid;
            else lo = mid;
        }
        
        if (hi == sz(prefmin)) l = -prefmin.back();
        else
        {
            if (delta[hi] > 0) l = -prefmin[hi];
            else l = balls[i] - (balls[i-1]+prefmax[hi]);
        }

        int r = 0;
        lo = -1;
        hi = sz(prefmin);
        while (lo + 1 < hi)
        {
            int mid = (lo + hi) / 2;
            int mhi = balls[i] + prefmax[mid];
            int plo = balls[i + 1] + prefmin[mid];
            if (mhi >= plo) hi = mid;
            else lo = mid;
        }

        if (hi == sz(prefmin)) r = prefmax.back();
        else
        {
            if (delta[hi] > 0) r = (balls[i+1]+prefmin[hi]) - balls[i];
            else r = prefmax[hi];
        }
        

        cout << l + r << "\n";
    }

    return 0;
}
