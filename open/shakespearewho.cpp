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

void dfs(int u, vi& vis, vector<vector<p2>>& adj, vi& order) {
    if (vis[u]==1) {
        cout << "Shakespeare, who?\n";
        exit(0);
    }
    if (vis[u]==2) return;
    vis[u]=1;

    repe(e,adj[u]) dfs(e.first,vis,adj,order);
    order.push_back(u);
    vis[u]=2;
}

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
        HashInterval() {}
        HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
                pw[0] = 1;
                repp(i,0,sz(str))
                        ha[i+1] = ha[i] * C + str[i],
                        pw[i+1] = pw[i] * C;
        }
        H hashInterval(int a, int b) { // hash [a, b)
                return ha[b] - ha[a] * pw[b - a];
        }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<string> s(n);
    rep(i,n) cin >> s[i];
    sort(all(s));
    s.erase(unique(all(s)), end(s));
    vector<vector<p2>> adj(n);
    vector<HashInterval> h(n);
    vector<HashInterval> hrev(n);
    rep(i,n) h[i]=HashInterval(s[i]);

    rep(i,n) {
        rep(j,n) {
            if (i==j) continue;
            int lcp=0;
            HashInterval& h1 = h[i];
            HashInterval& h2 = h[j];
            repp(l,1,min(sz(s[i]), sz(s[j]))) {
                if (h1.hashInterval(0,l)==h2.hashInterval(sz(s[j])-l, sz(s[j]))) {
                    lcp=l;
                }
            }
            if (lcp) {
                adj[i].emplace_back(j,lcp);
            }
        }
    }

    vi vis(n),order;
    rep(i,n) dfs(i,vis,adj,order);
    vi dp(n);
    reverse(all(order));
    repe(u,order) {
        for (auto [e,w] : adj[u]) {
            dp[e]=max(dp[e],dp[u]+w);
        }
    }
    cout << *max_element(all(dp)) << '\n';


    return 0;
}
