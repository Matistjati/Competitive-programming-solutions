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
    
    int n;
    cin >> n;
    vvi guess(10, vi(n));

    rep(i, n) rep(j, 10) guess[j][i] = (i & (1 << j)) > 0;
    vector<string> res(10);
    rep(j, 10)
    {
        cout << "? ";
        rep(i, n) cout << guess[j][i];
        cout << endl;
        cin >> res[j];
    }

    cout << "! ";
    rep(i, n)
    {
        int col = 0;
        rep(j, 10) if (res[j][i]=='1') col += 1<<j;
        cout << col+1 << " ";
    }

    return 0;
}
