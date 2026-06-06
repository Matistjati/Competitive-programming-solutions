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

    p2 ans = {10000, 10000};
    int n;
    cin >> n;
    rep(i,n) {
        string s;
        cin >> s;
        int w = 0;
        int l = 0;

        int cnt=0;
        repe(c,s) {
            cnt++;
            if (c=='W') w++;
            else l++;
            if (w>=12) {
                ans=min(ans, p2(cnt,i));
            }

            if (l>=3) {
                l=w=0;
            }
        }
    }
    if (ans.first==10000) cout << "INCOMPLETE\n";
    else cout << ans.second+1 << '\n';

    return 0;
}
