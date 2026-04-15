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

int n;
#if !_LOCAL
string ask(vi q) {
    cout << "? ";
    for (int x : q) cout << x + 1 << ' ';
    cout << endl;
    string resp;
    cin >> resp;
    return resp;
}
#else
vi hidden;
string ask(vi q) {
    if (hidden.empty()) {
        hidden = vi(n);
        random_device rd;
        mt19937 rng(rd());
        //mt19937 rng(45);
        uniform_int_distribution<int> dist(0, n - 1);
        rep(i, n) hidden[i] = dist(rng);
        int maj = dist(rng);
        vi perm(n);
        iota(all(perm), 0);
        shuffle(all(perm),rng);
        rep(i, n / 2 + 1) {
            hidden[perm[i]] = maj;
        }
    }
    string res;
    rep(i, sz(hidden)) res += (hidden[i] == hidden[q[i]]) ? "1" : "0";
    return res;
}
#endif

struct UF {
    vi par, size;
    vector<set<int>> neg_adj;
    UF(int n) : par(n), size(n, 1), neg_adj(n) {
        iota(all(par), 0);
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
        repe(e, neg_adj[b]) {
            neg_adj[e].erase(b);
            neg_adj[e].insert(a);
            neg_adj[a].insert(e);
        }
    }
    void add_edge(int a, int b) {
        a = find(a);
        b = find(b);
        neg_adj[a].insert(b);
        neg_adj[b].insert(a);
    }
    bool has_edge(int a, int b) {
        a = find(a);
        b = find(b);
        return neg_adj[a].count(b);
    }
};

void solve() {
#if !_LOCAL
    cin >> n;
#else
    hidden.clear();
    n = 1e5;
#endif
    UF uf(n);

    auto apply_query = [&](vi& q, string& res) {
        rep(i, n) {
            if (res[i] == '1') {
                uf.merge(i, q[i]);
            }
            else {
                uf.add_edge(i, q[i]);
            }
        }
    };
    auto check_win = [&]() {
        rep(i, n) {
            if (uf.size[uf.find(i)] * 2 > n) {
                cout << "! " << i + 1 << endl;
                return true;
            }
        }
        return false;
    };
    auto cc = [&]() {
        map<int, vi> cc;
        rep(i, n) {
            cc[uf.find(i)].push_back(i);
        }
        vvi ccs;
        repe(c, cc) {
            ccs.push_back(c.second);
        }
        return ccs;
    };

    vi perm(n);
    iota(all(perm), 0);
    mt19937 rng(6969);
    shuffle(all(perm), rng);
    vi s(n);
    rep(i, n) s[perm[i]] = perm[(i + 1) % n];
    uniform_int_distribution<int> dist_n(0, n - 1);

    string res = ask(s);
    apply_query(s, res);
    if (check_win()) return;
    rep(it, 2) {
        vvi ccs = cc();
        int m_comp = 0;
        rep(i, sz(ccs)) m_comp = max<int>(m_comp, sz(ccs[i]));
        cerr << "After " << it + 1 << " queries, max is " << m_comp << '\n';

        vi cc_ind(sz(ccs));
        iota(all(cc_ind), 0);
        uniform_int_distribution<int> comp_dist(0, sz(ccs) - 1);
        vi guess(n, -1);
        set<p2> cc_pairs;
        vi sorted_cc_inds(sz(ccs));
        iota(all(sorted_cc_inds), 0);
        sort(all(sorted_cc_inds), [&](int a, int b) {
            return sz(ccs[a]) > sz(ccs[b]);
        });

        vi comp_weights;
        rep(i, sz(ccs)) {
            rep(j, sz(ccs[i])) comp_weights.push_back(i);
        }

        auto seen_pair = [&](int i, int j) {
            if (i == j) return true;
            if (i > j) swap(i, j);
            return cc_pairs.count(make_pair(i, j)) || uf.has_edge(ccs[i][0], ccs[j][0]);
        };

        auto add_pair = [&](int i, int j) {
            if (i > j) swap(i, j);
            cc_pairs.insert(make_pair(i, j));
        };

        rep(comp_ind, sz(ccs)) {
            vi& comp = ccs[comp_ind];
            if (sz(comp)>50) {
                shuffle(all(cc_ind), rng);
                int j = 0;
                rep(i, sz(comp)) {
                    int u = comp[i];
                    while (j<sz(ccs) && seen_pair(comp_ind, cc_ind[j])) {
                        j++;
                    }
                    if (j<sz(cc_ind)) {
                        ll o = cc_ind[j];
                        add_pair(comp_ind, o);
                        vi& o_comp = ccs[o];
                        uniform_int_distribution<int> dist_comp(0, sz(o_comp) - 1);
                        guess[u] = o_comp[dist_comp(rng)];
                    }
                    else { // this component is saturated
                        guess[u] = u;
                    }
                }
            }
            else {
                repe(u, comp) {
                    int o = -1;
                    rep(t, min(sz(sorted_cc_inds),100LL)) {
                        o = sorted_cc_inds[t];
                        if (!seen_pair(comp_ind,o)) break;
                    }

                    add_pair(comp_ind, o);
                    vi& o_comp = ccs[o];
                    uniform_int_distribution<int> dist_comp(0, sz(o_comp) - 1);
                    guess[u] = o_comp[dist_comp(rng)];
                }
            }
        }

        string res = ask(guess);
        apply_query(guess, res);
        if (check_win()) {
            cerr << "Won in " << it + 2 << " rounds\n";
            return;
        }

    }
    cout << "! -1" << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

#if _LOCAL
    rep(i, 1000) solve();
    return 0;
#else
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
#endif
}
