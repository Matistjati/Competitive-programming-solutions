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

    vi precomp = { 0 };
    int s = 1;
    rep(i, int(1e6))
    {
        if ((i+2)/2>s+1)
        {
            precomp.push_back(i-1);
            s = i;
        }
    }

    while (t--)
    {
        int q;
        cin >> q;
        q--;
        cout << 1+lower_bound(all(precomp), q) - begin(precomp) << "\n";
    }

    
    return 0;
}
