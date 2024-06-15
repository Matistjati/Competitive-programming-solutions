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
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int r, c, n;
    while (cin >> r >> c >> n && r!=0)
    {
        bool trans = 0;
        if (r > c) swap(r, c), trans = 1;
        vi activerow(r);
        vi activecol(c);
        vi activediag(r + c);
        vi activediag2(r + c);
        rep(i, n)
        {
            int a, b;
            cin >> a >> b;
            a--; b--;
            if (trans) swap(a, b);
            activerow[a] = 1;
            activecol[b] = 1;
            activediag[a - b + c-1] = 1;
            activediag2[a + b] = 1;
        }
        int ans = 0;
        rep(i, r) rep(j, c)
        {
            ans += activerow[i] == 0 && activecol[j] == 0 && activediag[i - j + c - 1] == 0 && activediag2[i + j] == 0;
        }
        cout << ans << "\n";
    }

    return 0;
}
