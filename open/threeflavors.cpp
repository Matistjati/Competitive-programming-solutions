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

    vector<p2> occs;
    occs.emplace_back(count(all(s),'a'), 'a');
    occs.emplace_back(count(all(s),'b'), 'b');
    occs.emplace_back(count(all(s),'c'), 'c');
    sort(all(occs));
    reverse(all(occs));

    string res(sz(s), '.');
    auto [cnt,c] = occs[0];
    if (cnt*2>sz(s)+1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < sz(s) && cnt > 0; i += 2, cnt--) {
        res[i]=c;
    }
    tie(cnt,c) = occs[1];
    for (int i = sz(s)-1; i >= 0 && cnt > 0;) {
        if (res[i]=='.') {
            res[i]=c;
            i-=2;
            cnt--;
        }
        else {
            i-=1;
        }
    }
    tie(cnt,c) = occs[2];
    rep(i,sz(s)) res[i] = res[i]=='.' ? c : res[i];
    cout << res << '\n';

    return 0;
}
