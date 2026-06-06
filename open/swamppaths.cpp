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

    int n, m;
    cin >> n >> m;

    map<p2, int> status;
    vector<tuple<string, int, int>> q(m);
    vi ans(m, -2);
    rep(i, m) {
        string s;
        int a, b;
        cin >> s >> a >> b;
        if (a > b)swap(a, b);
        q[i] = { s,a,b };
        if (s == "REMOVE") {
            status[p2(a, b)] = -1;
        }
        if (s == "ADD") {
            status[p2(a, b)] = 1;
        }
        if (s == "QUERY") {
            int s = status[p2(a, b)];
            ans[i] = s;
        }
    }
    status = map<p2, int>();
    reverse(all(q));
    rep(i, m) {
        auto [s, a, b] = q[i];
        int reali = m - 1 - i;
        if (s == "QUERY") {
            if (ans[reali] == 0) {
                int s = status[p2(a, b)];
                ans[reali] = s;
            }
        }

        if (s == "REMOVE") {
            status[p2(a, b)] = 1;
        }
        if (s == "ADD") {
            status[p2(a, b)] = -1;
        }
    }
    rep(i, m) if (ans[i] != -2) {
        int s = ans[i];
        if (s == 1) cout << "safe\n";
        if (s == 0) cout << "unsure\n";
        if (s == -1) cout << "unsafe\n";
    }

    return 0;
}
