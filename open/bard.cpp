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

    int n, e;
    cin >> n >> e;

    vector<bitset<100>> heard(n);
    int bardind = 0;
    rep(i, e)
    {
        int k;
        cin >> k;
        vi present(k);
        rep(j, k) cin >> present[j], present[j]--;
        sort(all(present));
        
        if (present[0]==0)
        {
            repe(p, present) heard[p][bardind] = 1;
            bardind++;
        }
        else
        {
            bitset<100> common;
            repe(p, present) common |= heard[p];
            repe(p, present) heard[p] |= common;
        }
    }

    rep(i, n)
    {
        bool good = 1;
        rep(j, bardind) good &= heard[i][j];
        if (good) cout << i + 1 << "\n";
    }

    return 0;
}
