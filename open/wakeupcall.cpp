#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;
    int s1 = 0, s2 = 0;
    rep(i, n)
    {
        int x;
        cin >> x;
        s1 += x;
    }
    rep(i, m)
    {
        int x;
        cin >> x;
        s2 += x;
    }

    if (s1 > s2)
    {
        cout << "Button 1";
    }
    else if (s2 > s1)
    {
        cout << "Button 2";
    }
    else cout << "Oh no";

    return 0;
}
