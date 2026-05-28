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

struct SatSolver {
    int n, timer = 0, scc = 0;
    vector<std::vector<int>> g;
    vector<int> low, id, comp, stk, ans;

    SatSolver(int n) : n(n), g(2*n), low(2*n), id(2*n), comp(2*n, -1), ans(n) {}

    int T(int i) const { return i * 2; }
    int F(int i) const { return i * 2 + 1; }
    int get(int i, int flip) {return flip ? T(i) : F(i); }

    void implies(int u, int v) {
        g[u].push_back(v);
        g[v ^ 1].push_back(u ^ 1); 
    }

    void dfs(int u) {
        low[u] = id[u] = ++timer;
        stk.push_back(u);
        for (int v : g[u]) {
            if (!id[v]) { dfs(v); low[u] = min(low[u], low[v]); }
            else if (comp[v] == -1) low[u] = min(low[u], id[v]);
        }
        if (low[u] == id[u]) {
            int v;
            do { v = stk.back(); stk.pop_back(); comp[v] = scc; } while (u != v);
            scc++;
        }
    }

    bool solve() {
        for (int i = 0; i < 2 * n; ++i) if (!id[i]) dfs(i);
        for (int i = 0; i < n; ++i) {
            if (comp[T(i)] == comp[F(i)]) return false;
            ans[i] = comp[T(i)] < comp[F(i)];
        }
        return true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m;
    cin >> n >> m;

    SatSolver sat(m);
    // 1 = reversed
    // 0 = not rev

    vector<pair<int,string>> strings(m);
    rep(i,m) {
        cin >> strings[i].first >> strings[i].second;
        strings[i].first--;
    }
    auto revindex = [&](int i, int ind, bool rev) {
        // transform to local coordinates
        ind -= strings[i].first;
        if (!rev) return strings[i].second[ind];
        return strings[i].second[sz(strings[i].second)-1-ind];
    };

    vector<int> isects;
    rep(i,n) {
        isects.clear();

        rep(j,m) {
            int p = strings[j].first;
            if (p>i) continue;
            int ending = p+sz(strings[j].second)-1;
            if (ending<i) continue;
            isects.push_back(j);
        }

        repe(a,isects) {
            repe(b,isects) {
                if (a==b) continue;

                rep(aval, 2) {
                    vector<bool> working;
                    rep(bval, 2) {
                        if (revindex(a,i,aval) == revindex(b,i,bval)) {
                            working.push_back(bval);
                        }
                    }

                    if (sz(working)==0) {
                        sat.implies(sat.get(a, aval), sat.get(a, !aval));
                    }
                    else if (sz(working)==1) {
                        sat.implies(sat.get(a, aval), sat.get(b, working[0]));
                    }
                    else {} // any is ok
                }

            }
        }
    }

    if (sat.solve()) {
        rep(i,m) if (sat.ans[i]) {
            reverse(all(strings[i].second));
        }
        string ans(n, '?');

        for (auto [p, s] : strings) {
            rep(o,sz(s)) {
                ans[o+p] = s[o];
            }
        }
        rep(i,n) if (ans[i]=='?') ans[i]='A';
        cout << ans << '\n';
    }
    else {
        cout << "Villa\n";
    }

    return 0;
}

