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

    string in;
    cin >> in;

    int dsum = 0;
    repe(c, in) dsum += c - '0';

    string ans(sz(in), '0');
    int i = 0;
    while (dsum>0)
    {
        if (dsum >= 9) ans[i] = '9', dsum -=9;
        else ans[i] = dsum + '0', dsum=0;
        i++;
    }

    string lo(sz(in), '0');
    dsum = 0;
    repe(c, in) dsum += c - '0';
    lo[0] = '1';
    dsum--;

    i = sz(in)-1;
    while (dsum > 0)
    {
        if (dsum >= 9) lo[i] += 9, dsum -= 9;
        else lo[i] += dsum, dsum = 0;
        i--;
    }


    cout << lo << " " << ans;

    return 0;
}
