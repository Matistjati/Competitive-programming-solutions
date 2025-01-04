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

    p2 ans = p2(0, 0);
    int n;
    cin >> n;
    auto collatz = [](int x)
        {
            int ret = 0;
            while (x!=1)
            {
                if (x % 2) x = x * 3 + 1;
                else x /= 2;
                ret++;
            }
            return ret;
        };
    repp(i, 1, n)
    {
        int c = collatz(i);
        if (c>ans.first)
        {
            ans = p2(c, i);
        }
    }
    cout << ans.second;

    return 0;
}
