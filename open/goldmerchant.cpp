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

struct UF {
    vi par;
    UF(int n) : par(n) {iota(all(par),0);}
    int find(int x) {return par[x]==x?x:par[x]=find(par[x]);}
    void merge(int a, int b) {
        par[find(a)]=find(b);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m;
    cin >> n >> m;

    vi val1(n), val2(n);

    rep(i,n) cin >>val1[i];
    rep(i,n) cin >>val2[i];

    UF uf(n);
    rep(i,m) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        uf.merge(a,b);
    }

    map<int,vi> groups;
    rep(i,n) {
        groups[uf.find(i)].push_back(i);
    }

    ll ans = 0;
    for (auto [_, group] : groups) {
        vi v1,v2;
        repe(u,group) v1.push_back(val1[u]), v2.push_back(val2[u]);
        sort(all(v1));
        sort(all(v2));
        rep(i,sz(v1)) ans += v1[i] * v2[i];
    }
    cout << ans << '\n';

    return 0;
}
