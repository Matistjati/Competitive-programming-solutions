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

    int n, a, b;
    cin >> n >> a >> b;
    int f = 0, bu = 0, fb = 0;
    repp(i, 1, n+1)
    {
        if (i % a == 0) f++;
        if (i % b == 0) bu++;
        if (i % a == 0 && i % b == 0) f--, bu--, fb++;
    }
    cout << f << " " << bu << " " << fb;

    return 0;
}
