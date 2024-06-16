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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define __builtin_popcountll popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;
    vi items(n);
    rep(i, n) cin >> items[i];
    sort(all(items));

    if (sz(items)<=m)
    {
        cout << *max_element(all(items));
        return 0;
    }

    vi firsthalf;
    rep(i, m)
    {
        firsthalf.push_back(items.back());
        items.pop_back();
    }
    reverse(all(firsthalf));
    reverse(all(items));
    int ans = 0;
    assert(sz(items));
    assert(sz(items) <= sz(firsthalf));
    rep(i, sz(items)) ans = max(ans, firsthalf[i] + items[i]);
    assert(ans>0);
    cout << max(ans, *max_element(all(firsthalf)));
    
    return 0;
}
