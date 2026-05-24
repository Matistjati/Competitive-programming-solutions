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

bitset<int(2e9)> seen;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<int> nums(n);
    int ans = -1;

    rep(i,n) {
        int x;
        cin >> x;
        nums[i]=x;
        if (seen[x]) {
            ans=x;
            break;
        }
        seen[x]=1;
    }

    rep(i,n) {
        if (nums[i]==ans) {
            cout << i+1 << ' ';
        }
    }
    cout << '\n';

    return 0;
}
