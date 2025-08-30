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

    int n, q;
    cin >> n;
    map<int, string> winner;
    rep(i, n)
    {
        string name;
        int g;
        cin >> name >> g;
        winner[g] = name;
    }
    cin >> q;

    while (q--)
    {
        int x;
        cin >> x;
        auto it = winner.upper_bound(x);
        if (it != winner.begin())
        {
            cout << prev(it)->second << "\n";
        }
        else
        {
            cout << ":(\n";
        }
    }

    return 0;
}
