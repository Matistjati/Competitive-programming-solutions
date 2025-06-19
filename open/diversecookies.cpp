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

signed main()
{
    fast();

    int n, a, b, c;
    cin >> n >> a >> b >> c;
    vi cook = { a,b,c };
    sort(all(cook));
    reverse(all(cook));
    a = cook[0];
    b = cook[1];
    c = cook[2];
    int k = b + c;
    if (k>=a)
    {
        cout << a + b + c;
    }
    else
    {
        int ans = 0;
        ans += 2 * k;
        a -= k;
        ans += min(n, a);
        cout << ans;
    }

    return 0;
}
