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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int r, h, s;
    while (cin >> r >> h >> s && r)
    {
        double side = sqrt(h * h - r * r);
        double angle = acos(double(r) / h);
        double length = (6.28318530718-2*angle) * r + side*2;
        cout << fixed << setprecision(2) << length * (100+s) / 100 << "\n";
    }

    return 0;
}
