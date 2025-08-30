#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int x;
    cin >> x;
    vi denoms = { 1,5,15,30,150 };
    vi ans(sz(denoms));
    while (x)
    {
        for (int i = sz(denoms) - 1; i >= 0; i--)
        {
            if (x >= denoms[i])
            {
                ans[i]++;
                x -= denoms[i];
                break;
            }
        }
    }
    repe(v, ans) cout << v << " ";

    return 0;
}
