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
    set<p2> tree1, tree2;
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        if (a < b) swap(a, b);
        tree1.insert(p2(a, b));
    }
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        if (a < b) swap(a, b);
        if (a < b) swap(a, b);
        tree2.insert(p2(a, b));
    }
    int common = 0;
    repe(u, tree2) if (tree1.count(u)) common++;
    cout << n-1-common << '\n';

    return 0;
}
