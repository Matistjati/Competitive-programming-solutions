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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

p2 ask(string q)
{
    cout << "? " << q << endl;
    p2 ret;
    cin >> ret.first >> ret.second;
    return ret;
}

signed main()
{
    fast();

    int r, c;
    cin >> r >> c;

    string q = "";
    rep(i, r - 1) q += "v";
    rep(i, c - 1) q += ">";
    p2 sw = ask(q);
    if (sw!=p2(r-1,c-1))
    {
        if (sw.first!=r-1)
        {
            cout << "! " << sw.first+1 << " " << 0 << endl;
            return 0;
        }
        cout << "! " << r-1 << " " << sw.second+1 << endl;
        return 0;
    }

    q = "";
    rep(i, r - 2) q += "v";

    rep(i, r - 1)
    {
        rep(j, c - 1) q += ">";
        q += "v>^";
        rep(j, c - 1) q += "<";
        q += "^";
    }
    rep(i, c - 1) q += ">";
    p2 ans = ask(q);
    cout << "! " << ans.first << " " << ans.second + 1 << endl;

    return 0;
}
