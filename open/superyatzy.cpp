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
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;
    vi cnt(6);
    rep(i, n)
    {
        int v;
        cin >> v;
        cnt[v-1]++;
    }
    rep(i, 6)
    {
        if (m+cnt[i]>=n)
        {
            cout << "Ja";
            return 0;
        }
    }
    cout << "Nej";


    return 0;
}
