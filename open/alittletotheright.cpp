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

    int n, p;
    cin >> n >> p;

    vvi trophies(n, vi(p));
    rep(i, n) rep(j, p) cin >> trophies[i][j];
    set<vi> ans;
    rep(j, p)
    {
        map<int, int> occs;
        rep(i, n)
        {
            occs[trophies[i][j]]++;
        }
        if (sz(occs) == n)
        {
            vector<p2> items(n);
            rep(i, n) items[i] = p2(trophies[i][j], i);
            sort(all(items));
            vi indices;
            repe(u, items) indices.push_back(u.second);
            ans.insert(indices);
        }
    }
    cout << sz(ans);


    return 0;
}
