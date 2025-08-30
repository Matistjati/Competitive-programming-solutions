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

    int q;
    cin >> q;
    set<string> guests;
    while (q--)
    {
        char action;
        string name;
        cin >> action >> name;
        if (action=='?')
        {
            cout << (guests.count(name) ? "Jebb" : "Neibb") << "\n";
        }
        else if (action=='+')
        {
            guests.insert(name);
        }
        else
        {
            guests.erase(name);
        }
    }

    return 0;
}
