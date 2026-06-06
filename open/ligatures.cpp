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

using ull = unsigned long long;
const int WIDTH = 256;
const int MAX_Q = 1e5;
const int Q_BLOCKS = (MAX_Q + WIDTH - 1) / WIDTH;

#include <immintrin.h>

using reg = unsigned long long __attribute__ ((vector_size (32)));

reg which_queries[Q_BLOCKS][26 * 26];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, Q, k;
    cin >> n >> Q >> k;


    string s;
    cin >> s;
    vector<int> pairs(n - 1);
    rep(i, n - 1) {
        pairs[i] = (s[i] - 'a') * 26 + s[i + 1] - 'a';
    }


    rep(q, Q) {
        string lig_in;
        cin >> lig_in;
        for (int i = 0; i < sz(lig_in); i += 2) {
            int a = lig_in[i] - 'a';
            int b = lig_in[i + 1] - 'a';

            which_queries[q / 256][a * 26 + b][(q % 256) / 64] |= 1ULL << (q % 64);
        }
    }

    rep(qblock, Q_BLOCKS) {
        auto& block_base = which_queries[qblock];
        reg active_queries{};
        reg adder[19]{};
        rep(i, n - 1) {
            active_queries = ~active_queries & block_base[pairs[i]];

            reg carry = active_queries;

            reg next_carry;
            #define add(j) \
                next_carry = adder[j] & carry; \
                adder[j] ^= carry; \
                carry = next_carry;

            add(0);
            add(1);
            add(2);
            add(3);
            add(4);
            add(5);
            add(6);
            add(7);
            add(8);
            add(9);
            add(10);
            if (_mm256_testz_si256(reinterpret_cast<__m256i>(carry), reinterpret_cast<__m256i>(carry))) continue;
            add(11);
            add(12);
            add(13);
            add(14);
            add(15);
            add(16);
            add(17);
            add(18);
        }

        rep(w, WIDTH) {
            int q = qblock * WIDTH + w;
            if (q >= Q) break;
            int ans = 0;
            
            int lane = w / 64;
            int bit  = w % 64;
            rep(j, 19) {
                if ((adder[j][lane] >> bit) & 1ULL) {
                    ans |= (1 << j);
                }
            }
            cout << ans << '\n';
        }
    }


    return 0;
}
