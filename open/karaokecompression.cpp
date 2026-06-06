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

typedef uint64_t ull;
struct H {
    ull x; H(ull x=0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        rep(i,sz(str))
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) { // hash [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;
    HashInterval h(s);
    int n = sz(s);

    vector<tuple<H,int,int>> occs;
    occs.reserve(n*n);
    
    rep(i,n) {
        repp(j,i,n) {
            occs.emplace_back(h.hashInterval(i,j+1),i,j);
        }
    }
    sort(all(occs));

    int ans = 1e9;
    auto handle_group = [&](span<tuple<H,int,int>> group) {
        int forbid_until = -1;
        int cnt = 0;
        for (auto [_,l,r] : group) {
            if (l<=forbid_until) continue;
            cnt++;
            forbid_until = r;
        }
        auto [_,l,r] = group[0];
        ans = min(ans, r-l+1 + cnt + n-cnt*(r-l+1));
    };

    for (int i = 0; i < sz(occs); ) {
        int j = i+1;
        while (j<sz(occs) && get<0>(occs[i])==get<0>(occs[j])) j++;
        handle_group(span<tuple<H,int,int>>(occs).subspan(i,j-i));
        i=j;
    }
    cout << ans << '\n';

    return 0;
}
