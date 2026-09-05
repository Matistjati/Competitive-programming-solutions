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
    
    vi lbooks, rbooks;
    int n,k;
    cin >> n >> k;
    rep(i,n) {
        int x;
        cin >> x;
        if (x>0) rbooks.push_back(x);
        if (x<0) lbooks.push_back(-x);
    }
    auto solve = [&](vi books, bool last_free) {
        sort(all(books));
        int ret = 0;
        while (sz(books)) {
            int cost = books.back();
            int s = sz(books);
            rep(i, min<int>(s, k)) books.pop_back();
            if (last_free && ret == 0) ret += cost;
            else ret += cost*2;
        }
        return ret;
    };

    cout << min(solve(lbooks, true) + solve(rbooks, false), solve(lbooks, false) + solve(rbooks, true)) << '\n';
    
    return 0;
}
