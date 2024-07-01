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

    int n, m;
    cin >> n >> m;
    if (m<n-1)
    {
        cout << "-1";
        return 0;
    }

    vector<p2> edges;
    rep(i, n - 1)
    {
        edges.emplace_back(i + 1, i + 2);
    }

    m -= n - 1;
    if (m>n-2)
    {
        cout << "-1";
        return 0;
    }
    rep(i, m)
    {
        edges.emplace_back(i + 1, i + 3);
    }
    repe(e, edges) cout << e.first << " " << e.second << "\n";

    return 0;
}
