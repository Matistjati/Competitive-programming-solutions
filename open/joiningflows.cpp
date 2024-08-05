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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int n;
    cin >> n;
    vector<tuple<int, int, int>> taps;
    int lo = 0;
    int hi = 0;
    rep(i, n)
    {
        int t, a, b;
        cin >> t >> a >> b;
        lo += a;
        hi += b;
        taps.emplace_back(t, a, b);
    }

    int q;
    cin >> q;
    while (q--)
    {
        int t, f;
        cin >> t >> f;
        if (f<lo || f>hi)
        {
            cout << "no\n";
            continue;
        }

        int templo = 0;
        int fc = f-lo;
        sort(taps.begin(), taps.end());
        repe(tap, taps)
        {
            int t, a, b;
            tie(t, a, b) = tap;
            templo += t * a;
            b -= a;
            if (fc>b)
            {
                fc -= b;
                templo += b * t;
            }
            else
            {
                templo += fc * t;
                fc = 0;
            }
        }
        
        int temphi = 0;
        fc = f-lo;
        sort(taps.rbegin(), taps.rend());
        repe(tap, taps)
        {
            int t, a, b;
            tie(t, a, b) = tap;
            temphi += t * a;
            b -= a;
            if (fc>b)
            {
                fc -= b;
                temphi += b * t;
            }
            else
            {
                temphi += fc * t;
                fc = 0;
            }
        }

        if (t*f >= templo && t*f <= temphi) cout << "yes\n";
        else cout << "no\n";
    }

    return 0;
}
