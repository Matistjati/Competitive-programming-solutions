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

    int n;
    cin >> n;

    vector<p2> shops;

    rep(i, n)
    {
        int a, b;
        cin >> a >> b;
        shops.emplace_back(b, a);
    }
    sort(all(shops));

    priority_queue<int> dp;

    int sum = 0;
    rep(i, n)
    {
        dp.emplace(shops[i].second);
        sum += shops[i].second;
        if (sum > shops[i].first)
        {
            sum -= dp.top();
            dp.pop();
        }
    }

    cout << dp.size();

    return 0;
}
