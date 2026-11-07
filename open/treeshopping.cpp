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
    
    int n,k;
    cin >> n >> k;
    vector<int> trees(n);
    rep(i,n) cin >> trees[i];

    deque<int> ma, mi;

    auto query = [&](deque<int>& dq, int i) {
        while ((i+1)-dq.front()>k) dq.pop_front();
        return trees[dq.front()];
    };

    int ans = 1e9;
    rep(i,n) {
        while (sz(ma) && trees[ma.back()] <= trees[i]) ma.pop_back();
        ma.push_back(i);
        while (sz(mi) && trees[mi.back()] >= trees[i]) mi.pop_back();
        mi.push_back(i);

        if (i+1>=k) {
            ans = min(ans, query(ma,i)-query(mi,i));
        }
    }
    cout << ans << '\n';
    
    return 0;
}
