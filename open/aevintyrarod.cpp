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

    ll n, x;
    cin >> n >> x;

    vector<pair<string, p2>> quests(n);
    repe(q, quests) cin >> q.first >> q.second.first >> q.second.second, q.second.first++;
    sort(all(quests), [](pair<string, p2>& x, pair<string, p2>& y)
        {
            auto [a, b] = x.second;
            auto [c, d] = y.second;
            return b * c + d > d * a + b;
        });

    repe(q, quests)
    {
        cout << q.first << "\n";
    }

    return 0;
}
