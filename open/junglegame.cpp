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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


bitset<4000000 * 5> forbidden;
signed main()
{
    fast();


    int n;
    cin >> n;
    vector<p2> pts(n);
    rep(i, n) cin >> pts[i].first >> pts[i].second;
    auto start = chrono::high_resolution_clock::now();

    vector<p2> valid_points;
    repp(i, 1, n + 1) repp(j, 1, n + 1) valid_points.emplace_back(i, j);
    mt19937 rng(10);

    auto getind = [](p2 p)
    {
        return 2001 * p.first + p.second;
    };

    rep(i, n) forbidden[getind(pts[i])] = 1;
    while (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count()<500)
    {
        shuffle(all(valid_points), rng);

        
        vector<p2> taken;

        int i = 0;
        while (sz(taken)<n&&i<sz(valid_points))
        {
            bool good = 1;
            p2 p = valid_points[i];
            taken.push_back(p);
            repe(u, taken)
            {
                if (forbidden[getind(p2(p.first+u.first,p.second+u.second))])
                {
                    good = 0;
                    break;
                }
            }

            if (!good)
            {
                taken.pop_back();
            }

            i++;
        }

        if (sz(taken)==n)
        {
            cout << "YES\n";
            repe(u, taken)
            {
                cout << u.first << " " << u.second << "\n";
            }
            return 0;
        }

    }

    cout << "NO";

    return 0;
}
