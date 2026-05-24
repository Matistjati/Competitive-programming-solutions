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

int P;
int timer = 0;
struct Tree {
    int n;
    vi modtime;
    vector<vector<p2>> additions;

    Tree(int n) : n(n), modtime(n * 4, -1), additions(n * 4) {}

    void add(int x, int l, int r, int ql, int qr, int v) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            if (sz(additions[x])) additions[x].emplace_back(timer, v + additions[x].back().second);
            else additions[x].emplace_back(timer, v);
            return;
        }
        int mid = (l + r) / 2;
        add(x * 2, l, mid, ql, qr, v);
        add(x * 2 + 1, mid + 1, r, ql, qr, v);
    }

    void mod(int x, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            modtime[x] = timer;
            return;
        }
        int mid = (l + r) / 2;
        mod(x * 2, l, mid, ql, qr);
        mod(x * 2 + 1, mid + 1, r, ql, qr);
    }

    ll pathmax(int x, int l, int r, int i) {
        if (l == r) return modtime[x];
        int mid = (l + r) / 2;
        if (i <= mid) return max(modtime[x], pathmax(x * 2, l, mid, i));
        return max(modtime[x], pathmax(x * 2 + 1, mid + 1, r, i));
    }

    p2 get_node(int x, int time_at) {
        if (additions[x].empty()) return { 0,0 };
        auto it = lower_bound(all(additions[x]), p2(time_at, -inf));
        if (it == end(additions[x])) return { additions[x].back().second,0};
        if (it == begin(additions[x])) return { 0, additions[x].back().second };
        return { prev(it)->second, additions[x].back().second - prev(it)->second };
    }

    p2 pathsum(int x, int l, int r, int i, int time_at) {
        p2 ret = get_node(x, time_at);
        if (l == r) return ret;
        int mid = (l + r) / 2;
        p2 merge;
        if (i <= mid) merge = pathsum(x * 2, l, mid, i, time_at);
        else merge = pathsum(x * 2 + 1, mid + 1, r, i, time_at);
        return { ret.first + merge.first,ret.second + merge.second };
    }

    ll get(int i) {
        ll p = pathmax(1, 0, n - 1, i);
        p2 psum = pathsum(1, 0, n - 1, i, p);
        return psum.first % P + psum.second;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q >> P;
    Tree tree(n);
    rep(i, n) {
        int x;
        cin >> x;
        tree.add(1, 0, n - 1, i, i, x);
    }

    auto print = [&]() {
        return;
        rep(i, n) {
            cout << tree.get(i) << ' ';
        }
        cout << '\n';
    };
    print();

    while (q--) {
        int kind;
        cin >> kind;
        if (kind == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--; r--;
            tree.add(1, 0, n - 1, l, r, x);
        }
        else if (kind == 2) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            timer++;
            tree.mod(1, 0, n - 1, l, r);
        }
        else {
            int i;
            cin >> i;
            i--;
            cout << tree.get(i) << '\n';
        }
        print();
    }


    return 0;
}
