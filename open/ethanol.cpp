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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int n;
    cin >> n;
    int k = 4 + 2 * n;
    vector<string> ans(5, string(k,' '));
    
    int i = 2;
    while (i<k-2)
    {
        ans[0][i] = 'H';
        ans[1][i] = '|';
        ans[2][i] = 'C';
        ans[2][i + 1] = '-';
        ans[3][i] = '|';
        ans[4][i] = 'H';
        i += 2;
    }
    ans[2][0] = 'H';
    ans[2][1] = '-';
    ans[2][k - 1] = 'H';
    ans[2][k - 2] = 'O';

    cout << ans[0] << "\n";
    cout << ans[1] << "\n";
    cout << ans[2] << "\n";
    cout << ans[3] << "\n";
    cout << ans[4] << "\n";
    
    return 0;
}

