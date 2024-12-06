#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int x;
    cin >> x;
    if (x == 1)
    {
        cout << 1;
        return 0;
    }
    if (x == 2)
    {
        cout << 2;
        return 0;
    }
    int p1 = 1, p2 = 1;
    x -= 2;
    rep(i, 1000)
    {
        int fib = p1 + p2;
        p2 = p1;
        p1 = fib;
        x -= fib;
        if (x<=0)
        {
            cout << i+3;
            return 0;
        }
    }


    return 0;
}
