#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

int permToInt(vector<int>& v) {
    int use = 0, i = 0, r = 0;
    for(int x:v) r = r * ++i + __builtin_popcount(use & -(1<<x)),
        use |= 1 << x;                     // (note: minus, not ~!)
    return r;
}

#include <immintrin.h>
vector<int> intToPerm(int r, int n) {
    vector<int> v(n);
    if (n <= 0) return v;

    unsigned int avail = (1U << n) - 1;
    unsigned int ur = r;
    int* out = v.data();

#define STEP(i) \
    { \
        unsigned int c = ur % i; ur /= i; \
        unsigned int mask = _pdep_u32(1U << (i - 1 - c), avail); \
        out[i - 1] = __builtin_ctz(mask); \
        avail ^= mask; \
    }

#define STEP1 { out[0] = __builtin_ctz(avail); }

    switch (n) {
        case 11: STEP(11) STEP(10) STEP(9) STEP(8) STEP(7) STEP(6) STEP(5) STEP(4) STEP(3) STEP(2) STEP1 break;
        case 10: STEP(10) STEP(9) STEP(8) STEP(7) STEP(6) STEP(5) STEP(4) STEP(3) STEP(2) STEP1 break;
        case 9:  STEP(9)  STEP(8) STEP(7) STEP(6) STEP(5) STEP(4) STEP(3) STEP(2) STEP1 break;
        case 8:  STEP(8)  STEP(7) STEP(6) STEP(5) STEP(4) STEP(3) STEP(2) STEP1 break;
        case 7:  STEP(7)  STEP(6) STEP(5) STEP(4) STEP(3) STEP(2) STEP1 break;
        case 6:  STEP(6)  STEP(5) STEP(4) STEP(3) STEP(2) STEP1 break;
        case 5:  STEP(5)  STEP(4) STEP(3) STEP(2) STEP1 break;
        case 4:  STEP(4)  STEP(3) STEP(2) STEP1 break;
        case 3:  STEP(3)  STEP(2) STEP1 break;
        case 2:  STEP(2)  STEP1 break;
        case 1:  STEP1 break;
        default: __builtin_unreachable();
    }

#undef STEP
#undef STEP1

    return v;
}


bitset<int(1e9)> vis;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m;
    cin >> n >> m;

    vector<int> target(n);
    iota(all(target),0);

    int t = permToInt(target);

    vector<int> start(n);
    rep(i,n) cin >> start[i];
    vector<pair<int,int>> swaps(m);
    for (auto& [u,v] : swaps) {
        cin >> u >> v;
        u--; v--;
    }
    
    using T = tuple<int,int,int>;
    priority_queue<T, vector<T>, greater<T>> q;
    auto push = [&](int d, int enc, vector<int>& perm) {
        int dis = 0;
        rep(i,n) dis += perm[i] != target[i];
        q.emplace(d+dis, d, enc);
    };
    push(0,permToInt(start),start);
    vis[permToInt(start)]=1;

    while (sz(q)) {
        auto [_, d, p_enc] = q.top();
        q.pop();

        if (p_enc==t) {
            cout << d << '\n';
            return 0;
        }

        vector<int> perm = intToPerm(p_enc, n);
        

        for (auto [u,v] : swaps) {
            swap(perm[u],perm[v]);
            int enc = permToInt(perm);
            swap(perm[u],perm[v]);
            if (vis[enc]) continue;
            vis[enc]=1;
            push(d+1,enc,perm);
        }
    }

    return 0;
}
