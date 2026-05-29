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
    vector<int> par, size;
    vector<p2> str;
    UF(int n) : par(n), size(n, 1), str(n) { iota(all(par), 0); }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
        str[a].first += str[b].first;
        str[a].second += str[b].second;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q;
    cin >> q;
    UF uf(q);
    map<string, int> remap;
    vector<string> names(q);

    vi dead(q);
    vector<p2> init_str(q);
    while (q--)
    {
        char c;
        cin >> c;
        if (c == 'u') {
            string a, b;
            cin >> a >> b;
            uf.merge(remap[a], remap[b]);
        }
        if (c == 'a') {
            string a, b;
            cin >> a >> b;
            cout << ((uf.find(remap[a]) == uf.find(remap[b])) ? "Aye" : "Nay") << '\n';
        }
        if (c == 'j') {
            string x;
            int a, b;
            cin >> x >> a >> b;
            remap[x] = sz(remap);
            names[remap[x]] = x;
            init_str[remap[x]] = {a,b};
            uf.str[remap[x]] = { a,b };
        }
        if (c == 's') {
            string x;
            cin >> x;
            cout << uf.str[uf.find(remap[x])].first << '\n';
        }
        if (c == 'w') {
            vector<string> alive;
            rep(i, sz(remap)) {
                if (!dead[i]) {
                    alive.push_back(names[i]);
                }
            }
            sort(all(alive));
            repe(u, alive) cout << u << '\n';
        }
        if (c=='r') {
            string x,y;
            cin >> x >> y;
            int a = remap[x];
            int b = remap[y];
            if (uf.find(a)==uf.find(b)) {
                cout << "Ye be a daft one! They be sailin' under the same flag!\n";
            }
            else {
                auto [as,ac] = uf.str[uf.find(a)];
                auto [bs,bc] = uf.str[uf.find(b)];
                if (as!=bs || (as==bs && ac!=bc)) {
                    if (as>bs || (as==bs && ac>bc)) {
                        cout << x << '\n';
                        dead[b] = 1;
                        uf.str[uf.find(b)].first -= init_str[b].first;
                        uf.str[uf.find(b)].second -= init_str[b].second;
                    }
                    else if (bs > as || (as==bs && bc > ac)) {
                        cout << y << '\n';
                        dead[a] = 1;
                        uf.str[uf.find(a)].first -= init_str[a].first;
                        uf.str[uf.find(a)].second -= init_str[a].second;
                    }
                    else {
                        assert(0);
                    }
                }
                else {
                    cout << "Arrr, both of them pirate crews be walkin' the plank!\n";
                    dead[a]=1;
                    dead[b]=1;
                }
            }
        }
    }


    return 0;
}

