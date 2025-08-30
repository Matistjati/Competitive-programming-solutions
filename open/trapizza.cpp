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

    int diam;
    int a, b, c;
    cin >> diam >> a >> b >> c;
    long double circle_area = diam * diam * 3.1415926535897932384;
    int trap_area = c * (a + b) * 2;
    if (circle_area > trap_area)
    {
        cout << "Mahjong!";
    }
    else if (circle_area < trap_area)
    {
        cout << "Trapizza!";
    }
    else
    {
        cout << "Jafn storar!";
    }


    return 0;
}
