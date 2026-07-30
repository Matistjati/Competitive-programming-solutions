#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

using vp2 = vector<p2>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll tx, ty;
    cin >> tx >> ty;

    vector<tuple<double,ll>> allb;
    vp2 joanna;
    vp2 opposite;

    rep(i, 6)
    {
        ll x, y;
        cin >> x >> y;
        joanna.emplace_back(x, y);
        allb.emplace_back((x-tx)*(x-tx) + (y - ty) * (y - ty), 1);
    }

    rep(i, 6)
    {
        ll x, y;
        cin >> x >> y;
        opposite.emplace_back(x, y);
        allb.emplace_back((x - tx) * (x - tx) + (y - ty) * (y - ty), 2);
    }

    sort(all(allb));

    ll closest = get<0>(allb[0]);
    repp(i, 1, 12)
    {
        if (get<0>(allb[i])==closest&&get<1>(allb[i])!=get<1>(allb[0]))
        {
            cout << "TIE";
            return 0;
        }
    }

    bool keepgoing = true;
    vi scores(3);
    ll i = 0;
    while (keepgoing && i < 12)
    {
        if (get<1>(allb[i])!=get<1>(allb[0]))
        {
            break;
        }
        scores[get<1>(allb[0])]++;
        i++;
    }

    if (get<1>(allb[0])==1)
    {
        cout << "Jonna" << "\n" << scores[1];
    }
    else
    {
        cout << "OPPONENTS" << "\n" << scores[2];

    }

    return 0;
}
