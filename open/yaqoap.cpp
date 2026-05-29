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
    vi par, size, compval;

    UF(int n) : par(n), size(n,1),compval(n) {
        iota(all(par),0);
    }
    int find(int x) {return par[x]==x?x:par[x]=find(par[x]);}
    void merge(int a, int b) {
        a=find(a);b=find(b);
        if (a==b) return;
        if (size[a]<size[b]) swap(a,b);
        par[b]=a;
        size[a]+=size[b];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vi nums(n);
    rep(i,n) cin >> nums[i];

    map<int,vi> where;
    rep(i,n) where[nums[i]].push_back(i);

    UF uf(n);
    for (auto [_, group] : where) {
        rep(i,sz(group)-1) {
            uf.merge(group[i],group[i+1]);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        int ans = uf.size[uf.find(a)];
        uf.merge(a,b);
        cout << ans << ' ' << uf.size[uf.find(a)] << '\n';
    }

    return 0;
}

