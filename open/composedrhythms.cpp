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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int n;
    cin >> n;
    if (n%2==0)
    {
        cout << n / 2 << "\n";
        rep(i, n / 2) cout << "2 ";
    }
    else
    {
        cout << (n - 3) / 2 + 1 << "\n";
        cout << "3 ";
        rep(i, (n - 3) / 2) cout << "2 ";
    }

    return 0;
}
