#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
const ll inf = 1e18;


int main() {
    cin.tie(0)->sync_with_stdio(0);

    set<int> blocked;
    int n,q;
    cin >> n >> q;
    rep(_,q) {
        char c;
        cin >> c;
        if (c=='-') {
            int x;
            cin >> x;
            x--;
            blocked.insert(x);
        }
        else if (c=='+') {
            int x;
            cin >> x;
            x--;
            blocked.erase(x);
        }
        else {
            int a,b;
            cin >> a >> b;
            a--; b--;
            if (a>b) swap(a,b);
            if (blocked.find(a) != blocked.end() || blocked.find(b) != blocked.end()) {
                cout << "impossible\n";
                continue;
            }
            auto clock = blocked.lower_bound(a);
            if (clock == blocked.end() || *clock > b) {
                cout << "possible\n";
                continue;
            }
            auto ee = blocked.lower_bound(b);
            if (ee != blocked.end()) {
                cout << "impossible\n";
                continue;
            }
            auto aa = blocked.lower_bound(0);
            if (*aa < a) {
                cout << "impossible\n";
                continue;
            }
            cout << "possible\n";
        }
    }

    return 0;

}
