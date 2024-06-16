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

    vvi dice(3, vi(6));
    rep(i, 3) rep(j, 6) cin >> dice[i][j];
    
    rep(i, 3)
    {
        int iwins = 1;
        rep(j, 3)
        {
            if (i == j) continue;
            int iwin = 0;
            int opponentwin = 0;
            int allsame = 1;
            repp(k, 1, 6) allsame &= dice[i][k] == dice[i][k - 1];
            if (allsame&&dice[i] == dice[j]) iwins = 0;
            rep(k, 6)
            {
                rep(l, 6)
                {
                    iwin += dice[i][l] > dice[j][k];
                    opponentwin += dice[j][k] > dice[i][l];
                }
            }
            if (opponentwin>iwin)
            {
                iwins = 0;
            }
        }
        if (iwins)
        {
            cout << i + 1;
            return 0;
        }
    }
    cout << "No dice";

    return 0;
}
