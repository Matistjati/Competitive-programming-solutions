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

    int n;
    cin >> n;
    int lb = 0;
    rep(i, n)
    {
        string x;
        cin >> x;
        if (x[0] == '/')
        {
            int x = 10 * ((lb + 10) / 10);
            cout << x << '\n';
        }
        else
        {
            int v = stoi(x);
            lb = max(lb, v);
            cout << v << '\n';
        }
    }

    return 0;
}
