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
#define __builtin_clz 
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int n;
    cin >> n;
    map<string, vi> visits;
    rep(i, n)
    {
        string name;
        int time;
        cin >> name >> time;
        visits[name].push_back(time);
    }
    repe(v, visits) sort(all(v.second));

    int q;
    cin >> q;
    while (q--)
    {
        string name;
        int k;
        cin >> name >> k;
        k--;
        cout << visits[name][k] << "\n";
    }

    return 0;
}
