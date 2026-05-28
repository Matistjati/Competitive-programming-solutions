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

struct UFReset {
    vector<int> par, size;
    vector<int> parsnapshot, sizesnapshot;
    vector<int> time_of;
    int timer = 0;

    UFReset(int n) : par(n), size(n, 1), time_of(n) {
        iota(all(par), 0);
    }

    int& getpar(int x) {
        if (time_of[x] != timer) {
            par[x] = parsnapshot[x];
            size[x] = sizesnapshot[x];
            time_of[x] = timer;
        }
        return par[x];
    }

    int& getsize(int x) {
        if (time_of[x] != timer) {
            par[x] = parsnapshot[x];
            size[x] = sizesnapshot[x];
            time_of[x] = timer;
        }
        return size[x];
    }

    int find(int x) { return getpar(x) == x ? x : getpar(x) = find(getpar(x)); }

    void merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (getsize(a) < getsize(b)) swap(a, b);

        getpar(b) = a;
        getsize(a) += getsize(b);
    }

    void take_snapshot() {
        parsnapshot = par;
        sizesnapshot = size;
    }

    void reset() {
        timer++;
    }
};

struct Frac {
    ll num, den;
    Frac(ll a, ll b) {
        ll g = gcd(abs(a), abs(b));
        a /= g;
        b /= g;
        num = a;
        den = b;
        if (den < 0) num = -num, den = -den;
    }
    bool operator<(const Frac& o) const {
        return num * o.den < o.num * den;
    }
    bool operator==(const Frac& o) const {
        return num == o.num && den == o.den;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    UFReset uf(n * n);

    vvi base(n, vi(n));
    vvi vel(n, vi(n));
    rep(i, n) rep(j, n) cin >> base[i][j];
    rep(i, n) rep(j, n) cin >> vel[i][j];

    auto ind = [&](int a, int b) {
        return a * n + b;
    };

    using ld = long double;
    vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
    vector<tuple<Frac, p2, p2>> isects;
    isects.reserve(n * n);
    rep(i, n) rep(j, n) {
        for (auto [di, dj] : dirs) {
            p2 np = { i + di,j + dj };
            if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= n) continue;
            auto [mybase, myvel] = p2(base[i][j], vel[i][j]);
            auto [theybase, theyvel] = p2(base[np.first][np.second], vel[np.first][np.second]);

            if (myvel == theyvel) {
                if (mybase == theybase) { // always together
                    uf.merge(ind(i, j), ind(np.first, np.second));
                }
                else {} // never equal
            }
            else {
                Frac isect = { theybase - mybase, myvel - theyvel };
                if (isect < Frac(0,1)) continue;
                isects.emplace_back(isect, p2(i, j), np);
            }
        }
    }
    uf.take_snapshot();

    int ans = *max_element(all(uf.size));

    sort(all(isects));

    auto process_equal = [&](span<tuple<Frac, p2, p2>> isects) {
        uf.reset();

        for (auto [_, a, b] : isects) {
            uf.merge(ind(a.first, a.second), ind(b.first, b.second));
            ans = max(ans, uf.getsize(uf.find(ind(a.first, a.second))));
        }
    };

    for (int i = 0; i < sz(isects);) {
        int j = i + 1;
        while (j < sz(isects) && get<0>(isects[i]) == get<0>(isects[j])) {
            j++;
        }
        // [i,j) are all equal
        process_equal(span(isects).subspan(i, j - i));
        i = j;
    }

    cout << ans << '\n';

    return 0;
}
