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

signed main()
{
    fast();

    int r, g, b, k;
    cin >> r >> g >> b >> k;
    if (g||b)
    {
        cout << r + k;
    }
    else
    {
        if (r)
        {
            if (k>1) cout << r + k - 2;
            else cout << r;
        }
        else cout << 0;
    }

    return 0;
}
