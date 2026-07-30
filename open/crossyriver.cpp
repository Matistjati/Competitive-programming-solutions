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

struct Log {
    ll row, col, dcol;
};

using T = tuple<ll,ll,int>;

static inline uint32_t u32_first(const T& x)  { return (uint32_t)get<0>(x); }
static inline uint32_t u32_second(const T& x) { return (uint32_t)get<1>(x); }
static inline uint32_t u32_third(const T& x)  { return (uint32_t)get<2>(x); }

void radix_sort_tuples(vector<T>& a) {
    const int n = (int)a.size();
    if (n <= 1) return;

    vector<T> b(n);

    auto counting_sort_third = [&]() {
        static int cnt[1001];
        memset(cnt, 0, sizeof(cnt));

        for (const auto& x : a) {
            ++cnt[u32_third(x)];
        }

        int pos = 0;
        for (int i = 0; i <= 1000; ++i) {
            int c = cnt[i];
            cnt[i] = pos;
            pos += c;
        }

        for (const auto& x : a) {
            b[cnt[u32_third(x)]++] = x;
        }
        a.swap(b);
    };

    auto radix16 = [&](auto key_of) {
        static int cnt[1 << 16];

        for (int shift = 0; shift < 32; shift += 16) {
            memset(cnt, 0, sizeof(cnt));

            for (const auto& x : a) {
                ++cnt[(key_of(x) >> shift) & 65535u];
            }

            int pos = 0;
            for (int i = 0; i < (1 << 16); ++i) {
                int c = cnt[i];
                cnt[i] = pos;
                pos += c;
            }

            for (const auto& x : a) {
                b[cnt[(key_of(x) >> shift) & 65535u]++] = x;
            }
            a.swap(b);
        }
    };

    // Least significant field first.
    counting_sort_third();
    radix16([](const T& x) { return u32_second(x); });
    radix16([](const T& x) { return u32_first(x); });
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    auto start = chrono::high_resolution_clock::now();

    ll R,C,n;
    cin >> R >> C >> n;
    vector<Log> logs(n);
    vi row_occs(R);
    rep(i,n) {
        ll r,t,v;
        string s;
        cin >> r >> t >> v >> s;
        r--;
        ll col = (s=="L") ?
            -t*v :
            (C-1)+t*v;
        ll dcol = (s=="L") ? v : -v;
        logs[i] = {r,col,dcol};
        row_occs[r]++;
    }

    int minrow = min_element(all(row_occs))-begin(row_occs);

    vector<Log> pivotlogs;
    rep(i,n) {
        auto [r,c,dc] = logs[i];
        if (r==minrow) {
            pivotlogs.push_back({r,c,dc});
        }
    }

    vector<tuple<ll,ll,int>> isects;
    for (auto [r1,c1,dc1] : pivotlogs) {
        isects.clear();
        int mx = 0;
        vi free_rows(R);
        free_rows[r1] = 1;
        for (auto [r2,c2,dc2] : logs) {
            if (r1==r2) continue;
            // c1+t*dc1=c2+t*dc2
            // t=(c2-c1)/(dc1-dc2)
            ll num = c2-c1;
            ll denom = dc1-dc2;
            if (denom==0) {
                free_rows[r2] |= c1==c2;
                continue;
            }
            if (num%denom != 0) {
                continue; // never intersect
            }
            ll isect_time = num/denom;
            if (isect_time<1) continue;
            __int128 isect_col = c1+__int128(isect_time)*dc1;
            if (isect_col < 0 || isect_col >= C) continue;
            isects.emplace_back(isect_time, isect_col, r2);
        }

        int num_free = accumulate(all(free_rows), 0);
        if (num_free==R) {
            cout << "YES\n";
            ll ans = (dc1 > 0) ? (-c1 / dc1) : (-(c1 - (C - 1)) / dc1);
            cout << ans << '\n';
            exit(0);
        }

        radix_sort_tuples(isects);
        auto handle_time = [&](span<tuple<ll,ll,int>> logs) {
            if (logs.empty() || sz(logs)+num_free<R) return; // cheeky early break
            ll curr_time = get<0>(logs[0]);
            vector<p2> cols;
            cols.reserve(sz(logs));
            for (auto [_,col,row] : logs) cols.push_back({col,row});

            // group by columns and check
            auto check_good = [&](span<p2> pts) {
                if (pts.empty() || sz(pts) + num_free < R) return;
                int row_count = !free_rows[pts[0].second];
                repp(i,1,sz(pts)) {
                    row_count += (!free_rows[pts[i].second]) && (pts[i].second != pts[i-1].second);
                }
                if (row_count+num_free==R) {
                    cout << "YES\n";
                    cout << curr_time << '\n';
                    exit(0);
                }
            };
            for (int i = 0; i < cols.size(); ) {
                int j = i + 1;
                while (j < sz(cols) && cols[j].first == cols[i].first) {
                    j++;
                }
                check_good(span<p2>(cols).subspan(i, j - i));
                i = j;
            }
        };

        for (int i = 0; i < isects.size(); ) {
            int j = i + 1;
            while (j < sz(isects) && get<0>(isects[j]) == get<0>(isects[i])) {
                j++;
            }
            handle_time(span<tuple<ll,ll,int>>(isects).subspan(i, j - i));
            i = j;
        }
    }

    cout << "NO\n";

    return 0;
}
