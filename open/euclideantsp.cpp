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

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    double p, s, v;
    cin >> n >> p >> s >> v;


    auto computer_time = [&](double c)
    {
        double sqrt2 = sqrt(2);
        return n*pow(log2(n), c * sqrt(2)) / (p * 1e9);
    };

    auto flight_time = [&](double c)
    {
        return s * (1 + 1 / c) / v;
    };

    auto cost = [&](double c)
    {
        return computer_time(c) + flight_time(c);
    };

    double lo = 0;
    double hi = 100;
    rep(i, 1000)
    {
        double a = lo + (hi - lo) / 3;
        double b = hi - (hi - lo) / 3;
        if (cost(a)<cost(b))
        {
            hi = b;
        }
        else
        {
            lo = a;
        }
    }
    cout << fixed << setprecision(15) << cost(lo) << " " << lo << '\n';

    return 0;
}
