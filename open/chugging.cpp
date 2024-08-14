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

    int k;
    cin >> k;

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int at = 0;
    int bt = 0;
    rep(i, k)
    {
        at += a + b * i;
        bt += c + d * i;
    }
    if (at==bt)
    {
        cout << "=";
    }
    else if (at<bt)
    {
        cout << "Alice";
    }
    else
    {
        cout << "Bob";
    }

    return 0;
}
