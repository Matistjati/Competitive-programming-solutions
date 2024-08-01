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

    int n;
    cin >> n;

    map<double, vector<tuple<double, double, int>>> events;
    rep(i, n)
    {
        double ax, ay, bx, by;
        cin >> ax >> ay >> bx >> by;
        events[ax].emplace_back(ay, by, 1);
        events[bx].emplace_back(ay, by, -1);
    }

    multiset<pair<double, int>> evs;
    double INVALID = -inf;
    double last = INVALID;

    double ans = 0;
    repe(ev, events)
    {
        if (last != INVALID)
        {
            double d = ev.first - last;

            double area = 0;

            int num_active = 0;
            double last_pos = INVALID;
            repe(uv, evs)
            {
                if (num_active && last_pos != INVALID)
                {
                    area += uv.first - last_pos;
                }
                last_pos = uv.first;
                num_active += uv.second;
            }

            ans += area * d;
        }

        repe(u, ev.second)
        {
            double a, b, t;
            tie(a, b, t) = u;
            if (t == 1)
            {
                evs.emplace(a, 1);
                evs.emplace(b, -1);
            }
            else
            {
                evs.erase(evs.find(pair<double,int>(a, 1)));
                evs.erase(evs.find(pair<double,int>(b, -1)));
            }
        }

        last = ev.first;
    }
    cout << fixed << setprecision(2) << ((double)ans);

    return 0;
}
