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

    int n,m;
    cin >> n >> m;
    rep(a,n+1) {
        rep(b,n+1) {
            if (a+b==n) {
                if (a*4+b*2==m) {
                    cout << a << '\n';
                    return 0;
                }
            }
        }
    }
    cout << "Rong talning\n";
    

    return 0;
}

