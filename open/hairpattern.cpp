#pragma GCC optimize("O3,unroll-loops")
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

consteval int pow3(int x) {
    int ret = 1;
    rep(i, x) ret *= 3;
    return ret;
}
constexpr int pow3s[9] = {
    pow3(0),
    pow3(1),
    pow3(2),
    pow3(3),
    pow3(4),
    pow3(5),
    pow3(6),
    pow3(7),
    pow3(8)
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    using ull = unsigned long long;
    ull given = 0, goal = 0;

    rep(i, n) {
        string s;
        cin >> s;
        rep(j, m) {
            if (s[j] == 'W') given += 1ULL << (i * m + j);
        }
    }
    rep(i, n) {
        string s;
        cin >> s;
        rep(j, m) {
            if (s[j] == 'W') goal += 1ULL << (i * m + j);
        }
    }
    ull rowmasks[8]{}, colmasks[8]{};
    rep(i, 8) {
        ull mask = 0;
        rep(j, m) mask |= 1ULL << (i * m + j);
        rowmasks[i] = mask;
    }

    rep(j, 8) {
        ull mask = 0;
        rep(i, n) mask |= 1ULL << (i * m + j);
        colmasks[j] = mask;
    }

    unsigned char goalrows[8]{};
    rep(i, n) {
        rep(j, m) if (goal & (1ULL << (i * m + j))) goalrows[i] |= 1ULL << j;
    }

    int ans = n * m;
    rep(colmask, pow3s[m]) {
        ull me = given;
        int zero_mask = 0;
        vi nonzero;
        rep(i, m) {
            int res = (colmask / pow3s[i]) % 3;
            if (res == 0) zero_mask |= 1 << i;
            if (res == 1) me |= colmasks[i], nonzero.push_back(i);
            if (res == 2) me &= ~colmasks[i], nonzero.push_back(i);
        }
        unsigned char rows[8]{};
        rep(i, n) {
            rep(j, m) if (me & (1ULL << (i * m + j))) rows[i] |= 1ULL << j;
        }
        int pcnt[8][256];
        rep(r,8) rep(i,256) pcnt[r][i] = popcount((unsigned int)i^goalrows[r]);
        do {
            if (rand()%4) continue; // cheeky optimization
            int cost = 0;
            rep(r, n) {
                int* __restrict pop = pcnt[r];
                int localcost = pop[rows[r]];
                { // lick to 1
                    unsigned char row = rows[r];
                    row |= zero_mask;
                    localcost = min(localcost, pop[row]);
                    for (auto i : nonzero) {
                        row |= 1 << i;
                        localcost = min(localcost, pop[row]);
                    }
                }
                { // lick to 0
                    unsigned char row = rows[r];
                    row &= ~zero_mask;
                    localcost = min(localcost, pop[row]);
                    for (auto i : nonzero) {
                        row &= ~(1 << i);
                        localcost = min(localcost, pop[row]);
                    }
                }
                cost += localcost;
                if (cost >= ans) break;
            }
            ans = min(ans, cost);
        } while (next_permutation(all(nonzero)));
    }
    cout << n * m - ans << '\n';

    return 0;
}
