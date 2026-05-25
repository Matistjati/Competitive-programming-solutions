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
    UF(int n) : par(n) {
        iota(all(par), 0);
    }
    int find(int x) { return par[x]==x?x:par[x]=find(par[x]);}
    void merge(int a, int b) {
        a=find(a); b=find(b);
        par[b]=a;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m;
    cin >> n >> m;
    string s,t;
    cin >> s >> t;

    UF uf(n);
    rep(i,m) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        uf.merge(a,b);
    }

    auto sort_string = [&](const string& s) {
        vector<vector<char>> comp_chars(n);
        vvi comp_indices(n);
        rep(i,n) comp_indices[uf.find(i)].push_back(i), comp_chars[uf.find(i)].push_back(s[i]);
        rep(i,sz(comp_chars)) sort(all(comp_chars[i])), reverse(all(comp_chars[i]));

        string ret(n, '-');

        rep(comp, n) {
            for (auto ind : comp_indices[comp]) {
                ret[ind] = comp_chars[comp].back();
                comp_chars[comp].pop_back();
            }
        }

        rep(i,n) assert(ret[i]!='-');
        return ret;
    };

    cout << (sort_string(s) == sort_string(t) ? "Yes" : "No") << '\n';

    return 0;
}
