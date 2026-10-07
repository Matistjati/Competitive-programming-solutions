#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
using vi = vector<ll>;

using ull = unsigned long long;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n,k;
    cin >> n >> k;

    mt19937_64 rng(42);
    vector<int> perm(k);
    vector<ull> w(k);
    rep(i,k) perm[i] = i, w[i] = rng();

    unordered_map<ull,ll> cnt;
    cnt.reserve(2e6);
    ull h = 0;
    cnt[h]++;

    rep(i,n) {
        int a,b;
        cin >> a >> b;
        a--; b--;

        h -= w[a] * perm[a] + w[b] * perm[b];
        swap(perm[a],perm[b]);
        h += w[a] * perm[a] + w[b] * perm[b];
        cnt[h]++;
    }

    ll ans = 0;
    for (auto [_,cn] : cnt) {
        ans += cn*(cn-1)/2;
    }

    cout << ans << '\n';

    return 0;
}
