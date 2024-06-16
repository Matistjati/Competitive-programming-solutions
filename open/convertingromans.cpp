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

    map<char, int> val;
    val['I'] = 1;
    val['V'] = 5;
    val['X'] = 10;
    val['L'] = 50;
    val['C'] = 100;
    val['D'] = 500;
    val['M'] = 1000;
    int n;
    cin >> n;
    while (n--)
    {
        string x;
        cin >> x;

        vi sign(sz(x), 1);
        int largest = 0;
        for (int i = sz(x) - 1; i >= 0; i--)
        {
            if (val[x[i]] < largest) sign[i] = -1;
            largest = max(largest, val[x[i]]);
        }

        int t = 0;
        rep(i, sz(x)) t += sign[i] * val[x[i]];

        cout << t << "\n";
    }

    return 0;
}
