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
    
    using ld = long double;
    ld T,a,b,c,d;
    cin >> T >> a >> b >> c >> d;
    auto eval = [&](ld t) {
        return powl(t-a, 6) + powl(t-b, 4) + powl(t-c, 2) + d + t;
    };

    auto isect = [&](ld lo, ld hi) {
        rep(i,100) {
            ld mid = (lo+hi)/2;
            if (eval(mid)<=T) hi = mid;
            else lo = mid;
        }
        return lo;
    };


    ld lo = -T, hi = T;
    rep(i,100) {
        ld l = lo + (hi-lo)/3;
        ld r = hi - (hi-lo)/3;
        if (eval(l)<eval(r)) hi = r;
        else lo = l;
    }
    if (eval(lo)>T) {
        cout << "O nei!\n";
        return 0;
    }
    ld x1 = isect(-T, lo);
    ld x2 = isect(T, lo);
    vector<ld> cands = {x1,x2};
    sort(all(cands));
    for (ld x : cands) {
        if (x>=0&&x<=T && abs(eval(x)-T) <= 1e-6) {
            cout << fixed << setprecision(15) << x << '\n';
            return 0;
        }
    }
    cout << "O nei!\n";
    
    return 0;
}
