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
    vector<tuple<int, int, int>> flights;
    rep(i, n) rep(j, n)
    {
        int v;
        cin >> v;
        if (v!=-1)
        {
            flights.emplace_back(i, j, v);
        }
    }
    sort(all(flights));
    cout << sz(flights) << "\n";
    repe(f, flights)
    {
        cout << get<0>(f)+1 << " " << get<1>(f)+1 << " " << get<2>(f) << "\n";
    }

    return 0;
}
