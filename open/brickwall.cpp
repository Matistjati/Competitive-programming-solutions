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

bool seen[301][301][301];
vector<int> arr;
void solve(int a, int b, int c, int t) {
    if (seen[a][b][c]) return;
    seen[a][b][c]=1;

    auto it = lower_bound(all(arr), t);
    
    if (*it==t) {
        if (next(it)==end(arr)) {
            cout << "YES\n";
            exit(0);
        }
        return;
    }

    if (a) solve(a-1,b,c,t+1);
    if (b) solve(a,b-1,c,t+2);
    if (c) solve(a,b,c-1,t+3);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,a,b,c;
    cin >> n >> a >> b >> c;

    arr.resize(n);
    rep(i,n) cin >> arr[i];
    partial_sum(all(arr),begin(arr));

    solve(a,b,c,0);
    cout << "NO\n";

    return 0;
}
