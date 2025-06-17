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

    int p, n;
    cin >> p >> n;
    set<string> seen;
    rep(i, n)
    {
        string x;
        cin >> x;
        seen.insert(x);
        if (sz(seen) == p)
        {
            cout << i + 1;
            return 0;
        }
    }
    cout << "paradox avoided";

    return 0;
}
