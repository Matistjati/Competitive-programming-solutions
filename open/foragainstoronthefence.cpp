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

    ll a, b, c, d, u;
    cin >> a >> b >> c >> d >> u;
    ll dx = (a - c);
    ll dy = (b - d);
    ll dist = dx * dx + dy * dy;
    if (dist==u)
    {
        cout << "on the fence\n";
    }
    else if (dist<u)
    {
        cout << "for\n";
    }
    else
    {
        cout << "against\n";
    }


    return 0;
}
