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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();


    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;
    auto avg = [](int a, int b)
    {
        double ret = 0;
        repp(i, a, b + 1) ret += i;
        ret /= (b - a + 1);
        return ret;
    };
    double aa = avg(a1,b1)+avg(a2,b2);
    cin >> a1 >> b1 >> a2 >> b2;
    double bb = avg(a1, b1) + avg(a2, b2);


    if (aa == bb)
    {
        cout << "Tie";
    }
    else if (aa < bb)
    {
        cout << "Emma";
    }
    else cout << "Gunnar";

    return 0;
}
