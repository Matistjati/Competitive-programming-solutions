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
#if _LOCAL
vi hidden;
int qn = 0;
int ask(int l, int r) {
    qn++;
    if (hidden.empty()) {
        hidden.resize(n);
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> dist(1, n);
        rep(i, n) hidden[i] = 1;
        // rep(i, n) hidden[i] = dist(rng);
    }

    set<int> vals;
    repp(i, l, r+1) vals.insert(hidden[i]);
    return sz(vals);
}
void resp(vi& x) {
    
}
void resp1(vi& x) {
    rep(i, sz(x)) rep(j, sz(x)) {
        if (x[i] != x[j]) {
            assert(hidden[i] != hidden[j]);
        }
        else {
            assert(hidden[i] == hidden[j]);

        }
    }
}
#else
int ask(int l, int r) {
    cout << "? " << l+1 << " " << r+1 << endl;
    char c;
    int res;
    cin >> c >> res;
    return res;
}
void resp(vi& x) {
    cout << "! ";
    repe(u, x) cout << u << ' ';
    cout << endl;
}
#endif

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    vi which_group(n, -1);
    vi seen(n);
    auto myask = [&](int l, int r) {
        fill(all(seen), 0);
        int ret = 0;
        repp(i, l, r + 1) {
            int x = which_group[i];
            ret += !seen[x];
            seen[x] = 1;
        }
        return ret;
    };
    int gind = 1;
    which_group[0] = 0;
    repp(i, 1, n) {
        int lo = -1;
        int hi = i+1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (ask(i - mid, i) == myask(i - mid, i-1)+1) lo = mid;
            else hi = mid;
        }
        if (hi == i+1) {
            which_group[i] = gind++;
        }
        else {
            which_group[i] = which_group[i-hi];
        }
        // int x = ask(1,i+1);
        // if (x==sz(nums)+1) {
        //     nums.push_back({});
        //     nums.back().push_back(i);
        // }
        // else {
        //     int lo = -1;
        //     int hi = sz(nums);
        //     while (lo+1<hi) {
        //         int mid = (lo+hi)/2;
        //         if (ask(1,mid))
        //     }
        // }
    }

    rep(i, n) which_group[i]++;
#if _LOCAL
    cerr << "win in " << qn << " questions\n";
    resp1(which_group);
#endif
    vi ans(n);
    vvi groups(gind+1);
    rep(i, n) groups[which_group[i]].push_back(i);
    int p = 0;
    repe(g, groups) {
        repe(u, g) {
            ans[p++] = u+1;
        }
    }
    resp(ans);

    return 0;
}

