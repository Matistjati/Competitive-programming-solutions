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

    string s;
    cin >> s;
    while (sz(s) % 3 != 0) s.insert(begin(s),'0');

    string ans;
    map<string,string> remap;
    remap["000"] = "0";
    remap["001"] = "1";
    remap["010"] = "2";
    remap["011"] = "3";
    remap["100"] = "4";
    remap["101"] = "5";
    remap["110"] = "6";
    remap["111"] = "7";

    while (sz(s)) {
        string last = s.substr(sz(s)-3);
        rep(i,3) s.pop_back();
        ans += remap[last];
    }

    reverse(all(ans));
    cout << ans << '\n';

    return 0;
}

