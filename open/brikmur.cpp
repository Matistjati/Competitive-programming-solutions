#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt,aes")
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

int ans=0;
const ll N = 1e9+7;
bitset<N> seen1;
using ull = unsigned long long;
void solve(int a, int b, int c, int w1, int w2) {
    if (w1>w2) swap(w1,w2);
    ull key = a + b*100 + c*100*100 + ll(w1) * 100*100*100;
    key %= N;
    if (seen1[key]) return;
    seen1[key]=1;

    int ret = 0;

    if (c) {
        if (w1+8==w2) {
            ans = max(ans,w2);
        }
        else {
            solve(a,b,c-1,w1+8,w2);
        }
    }

    if (b) {
        if (w1+4==w2) {
            ans = max(ans,w2);
        }
        else {
            solve(a,b-1,c,w1+4,w2);
        }
    }

    if (a) {
        if (w1+2==w2) {
            ans=max(ans,w2);
        }
        else {
            solve(a-1,b,c,w1+2,w2);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int a, b, c;
    cin >> a >> b >> c;
    solve(a, b, c, 0, 0);
    cout << ans << '\n';

    return 0;
}
