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

    int n;
    cin >> n;
    pair<int, string> best = { 1,"asd" };
    rep(i, n)
    {
        string name;
        int a, b;
        cin >> name >> a >> b;
        best = min(best, make_pair(-a * b, name));
    }
    cout << best.second << "\n";

    return 0;
}
