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

    string s;
    cin >> s;
    int a=0, b=0;

    repe(c, s)
    {
        if (c == 'H') a++;
        else b++;

        if ((a>=11 && a>=b+2) || (b>=11 && b>=a+2))
        {
            a = b = 0;
        }
    }
    cout << b << "-" << a;

    return 0;
}
