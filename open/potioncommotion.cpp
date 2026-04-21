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

    int n,m,p;
    cin >> n >> m >> p;

    int hp = n;
    rep(i,m) {
        int dmg;
        cin >> dmg;
        if (dmg >= hp) {
            while (p&&20+hp<=n) {
                hp+=20;
                p--;
            }
        }
        if (dmg >= hp) {
            if (p==0) {
                cout << "next time\n";
                return 0;
            }
            hp=n;
            p--;
        }
        hp -= dmg;
        if (hp <= 0) {
            cout << "next time\n";
            return 0;
        }
    }
    cout << "champion\n";

    return 0;
}
