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

    int t;
    cin >> t;
    while (t--)
    {
        int k;
        cin >> k;

        vi seen(k+1, -1);
        int f1 = 1;
        int f2 = 1;
        int ind = 2;
        while (true)
        {
            int f3 = f1 + f2;
            f3 %= k;
            if (seen[f3] != -1)
            {
                cout << seen[f3] << "\n";
                break;
            }
            seen[f3] = ind;
            ind++;
            f1 = f2;
            f2 = f3;
        }
    }

    return 0;
}
