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

    int n, m;
    cin >> n >> m;
    vector<string> menu(n);
    cin.ignore();
    rep(i, n)
    {
        string line;
        getline(cin, line);
        menu[i] = line;
    }
    map<string, int> progress;
    rep(i, m)
    {
        string line;
        getline(cin, line);
        cout << menu[progress[line]++] << '\n';
    }

    return 0;
}
