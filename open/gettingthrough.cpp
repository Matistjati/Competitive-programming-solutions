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

struct UF
{
    vi par;
    vi size;
    UF(int n) : par(n), size(n, 1)
    {
        rep(i, n)par[i] = i;
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

signed main()
{
    fast();
    
    int t;
    cin >> t;
    while (t--)
    {
        int w, n;
        cin >> w >> n;
        vi radii(n);
        vector<p2> pts(n);
        rep(i, n)
        {
            cin >> pts[i].first >> pts[i].second;
            cin >> radii[i];
        }

        auto dist = [](p2 a, p2 b)
            {
                int dx = a.first - b.first;
                int dy = a.second - b.second;
                return sqrt(dx * dx + dy * dy);
            };

        vector<tuple<double, int, int>> events;
        UF uf(n + 2);
        rep(i, n)
        {
            events.emplace_back(max(0LL, pts[i].first - radii[i]), i, n);
            events.emplace_back(max(0LL, w - pts[i].first - radii[i]), i, n+1);
            repp(j, i + 1, n)
            {
                events.emplace_back(max(0., dist(pts[i], pts[j]) - radii[i] - radii[j]), i, j);
            }
        }
        events.emplace_back(w, n, n + 1);
        sort(all(events));

        for (auto [d, u, v] : events)
        {
            uf.merge(u, v);
            if (uf.find(n)==uf.find(n+1))
            {
                cout << fixed << setprecision(15) << d/2 << "\n";
                break;
            }
        }
    }

    return 0;
}
