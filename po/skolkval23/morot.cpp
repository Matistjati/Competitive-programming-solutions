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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t, m;
    cin >> t >> m;

    int next_t = 0;
    int next_m = 0;
    int n_carrot = 40;

    int eaten_t = 0;
    int eaten_m = 0;

    int time = 0;
    while (n_carrot > 0) {
        if (next_t == time && next_m == time && n_carrot == 1) break;

        if (next_t == time)
        {
            n_carrot--;
            eaten_t++;
            next_t = time + t;
        }
        if (next_m == time)
        {
            n_carrot--;
            eaten_m++;
            next_m = time + m;
        }
        time++;
    }

    cout << eaten_t << " " << eaten_m << '\n';

    return 0;
}
