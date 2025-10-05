#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int x;
    cin >> x;
    repp(a, -999, 1000)
    {
        repp(b, -999, 1000)
        {
            if (a == 0 || b == 0) continue;
            if (a + b == x)
            {
                cout << a << " " << b << "\n";
                return 0;
            }
        }
    }

    return 0;
}
