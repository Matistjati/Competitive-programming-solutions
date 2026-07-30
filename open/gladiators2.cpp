#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

#define rep(i, b) for(ll i = 0; i < (b); i++)
#define repp(i, a, b) for(ll i = a; i < (b); i++)
#define repe(i,arr) for (auto& i : arr)
#define all(x) begin(x), end(x)
#define sz(x) ((ll)(x).size())
typedef pair<ll, ll> p2;
typedef vector<ll> vi;
typedef vector<vi> vvi;


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n, q;
    cin >> n >> q;
    vi skill(n);
    repe(v, skill) cin >> v;

    vi nextl(n), nextr(n);
    rep(i, n) nextl[i] = i - 1, nextr[i] = i + 1;

    vi deleted(n);

    function<ll(ll)> getl = [&](ll i) -> ll {
        if (i == -1) return i;
        if (deleted[i]) return nextl[i] = getl(nextl[i]);
        return i;
        };

    function<ll(ll)> getr = [&](ll i) -> ll {
        if (i == n) return i;
        if (deleted[i]) return nextr[i] = getr(nextr[i]);
        return i;
        };

    vi killedby(n, -1);
    while (q--)
    {
        ll u;
        char d;
        cin >> u >> d;

        if (d == '<')
        {
            ll p;
            while ((p = getl(u-1)) != -1 && skill[u] > skill[p])
            {
                killedby[p] = u;
                deleted[p] = 1;
            }
        }
        else
        {
            ll p;
            while ((p = getr(u+1)) != n && skill[u] > skill[p])
            {
                killedby[p] = u;
                deleted[p] = 1;
            }
        }
    }
    repe(u, killedby) cout << u << " ";
    cout << "\n";

    return 0;
}
