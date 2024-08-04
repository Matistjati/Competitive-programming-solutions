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

    int r, c;
    cin >> r >> c;

    map<char, int> cost;
    cost['.'] = 20;
    cost['O'] = 10;
    cost['\\'] = 25;
    cost['/'] = 25;
    cost['A'] = 35;
    cost['^'] = 5;
    cost['v'] = 22;
    int ans = 0;
    rep(i, r)
    {
        string row;
        cin >> row;
        rep(j, c) ans += cost[row[j]];
    }
    cout << ans;

    return 0;
}
