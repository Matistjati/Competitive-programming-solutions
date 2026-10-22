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
    HashInterval(const string& str) : ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        repp(i,0,sz(str))
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) { // hash [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
};

vector<H> getHashes(string& str, int length) {
    if (sz(str) < length) return {};
    H h = 0, pw = 1;
    repp(i,0,length)
        h = h * C + str[i], pw = pw * C;
    vector<H> ret = {h};
    repp(i,length,sz(str)) {
        ret.push_back(h = h * C + str[i] - pw * str[i-length]);
    }
    return ret;
}

H hashString(const string& s){H h{}; for(char c:s) h=h*C+c;return h;}

unordered_set<ull> all_hashes;
unordered_map<ull, bool> seen;
bool is_ok(const string& s) {
    H h = hashString(s);
    if (!all_hashes.count(h.get())) return false;
    if (sz(s)==1) return true;

    if (seen.count(h.get())) return seen[h.get()];

    string lhalf = s.substr(0, sz(s)-1);
    string rhalf = s.substr(1);

    return seen[h.get()] = (is_ok(lhalf) && is_ok(rhalf));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    map<string,int> strings;
    rep(i,n) {
        string s;
        cin >> s;
        strings[s] += 1;
    }
    all_hashes.reserve(n*2);
    for (auto [s, cnt] : strings) all_hashes.insert(hashString(s).get());

    int ans = 0;
    for (auto [s, cnt] : strings) {
        ans += is_ok(s) * cnt;
    }
    cout << ans << '\n';

    return 0;
}
