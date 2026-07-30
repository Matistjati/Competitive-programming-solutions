// optimizations: 
//  - radix sort
//  - only consider pairs S x T, where S is all s and T is all t. As opposed to All x All
//  - Not implemented: only consider portal candidates (u,v) with u < v
//  - Avoid allocating new memory, etc
//  - no emplace_back (WTF GCC LOCK IN)
#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
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

struct Event {
    Event(int x, int delta) : x(x), delta(delta) {}
    Event() {}
    int x;
    int delta; // Could be char, but then GCC generates worse code...
};

const int B = 12;
const int MASK = (1 << B) - 1;
const int PASSES = 3;
int cnt[1 << B] = { 0 };
int pref[1 << B];
vector<Event> tmp;

void radixsort(span<Event> events) {
    if (events.empty()) return;
    int n = events.size();

    tmp.resize(n); 

    int smallest = 0;
    for (const auto& ev : events) smallest = min(smallest, ev.x);

    Event* src = events.data();
    Event* dst = tmp.data();

    for (int pass = 0; pass < PASSES; pass++) {
        int shift = pass * B;

        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i)
            cnt[((src[i].x - smallest) >> shift) & MASK]++;

        pref[0] = 0;
        for (int i = 1; i < (1 << B); ++i)
            pref[i] = pref[i - 1] + cnt[i - 1];

        for (int i = 0; i < n; ++i) {
            int d = ((src[i].x - smallest) >> shift) & MASK;
            dst[pref[d]++] = src[i];
        }
        
        swap(src, dst);
    }

    copy(tmp.begin(), tmp.begin() + n, events.begin());
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,k;
    cin >> n >> k;
    vector<p2> people(k);
    set<int> l_endpoints_set, r_endpoints_set;
    for (auto& [a,b] : people) {
        cin >> a >> b;
        a--; b--;
        if (a>b) swap(a,b);
        l_endpoints_set.insert(a);
        r_endpoints_set.insert(b);
    }
    vi l_endpoints(all(l_endpoints_set));
    vi r_endpoints(all(r_endpoints_set));

    ll ans = 0;
    vector<Event> events(k*6+k);
    int num_events = 0;
    rep(s_i, sz(l_endpoints)) {
        int i = l_endpoints[s_i];
        num_events = 0;
        for (auto [a,b] : people) {
            ll y_f1 = abs(b-a)-1-abs(a-i);
            ll apex_f1 = b;
            // abs(x-apex_f1)+y_f1
            p2 f1_inter = {apex_f1-y_f1, min<ll>(n-1, apex_f1+y_f1)};

            // fn 1: (1+abs(a-i)) + abs(b-j)

            ll y_f2 = abs(b-a)-1-abs(b-i);
            ll apex_f2 = a;
            // abs(x-apex_f1)+y_f1
            p2 f2_inter = {apex_f2-y_f2, min<ll>(n-1, apex_f2+y_f2)};

            // No effect, skip
            if (y_f1 <= 0 && y_f2 <= 0) continue;

            // Only a single nonnegative one
            if (y_f1 <= 0 || y_f2 <= 0) {
                if (y_f2 > 0) {
                    swap(y_f1, y_f2);
                    swap(apex_f1, apex_f2);
                    swap(f1_inter, f2_inter);
                }
                events[num_events++] = {f1_inter.first, +1};
                events[num_events++] = {apex_f1, -2};
                events[num_events++] = {f1_inter.second, +1};
                continue;
            }

            // Separate
            events[num_events++] = {f1_inter.first, +1};
            events[num_events++] = {apex_f1, -2};
            events[num_events++] = {f1_inter.second, +1};

            events[num_events++] = {f2_inter.first, +1};
            events[num_events++] = {apex_f2, -2};
            events[num_events++] = {f2_inter.second, +1};
        }

        if (events.empty()) continue;

        span<Event> active_events = {events.begin(), events.begin()+num_events};
        radixsort(active_events);

        int eventslen = sz(events);
        repe(j, r_endpoints) {
            events[num_events++] = {j, 0};
        }
        inplace_merge(begin(events), begin(events)+eventslen, end(events), [](Event a, Event b) {
            return a.x < b.x;
        });

        active_events = {events.begin(), events.begin()+num_events};

        ll y = 0;
        ll dy = 0;
        ll prev_x = events[0].x;
        for (auto [x, delta] : active_events) {
            y += dy * (x - prev_x);
            prev_x = x;
            dy += delta;

            ans = max(ans, y);
        }
    }

    ans = -ans;
    for (auto [a,b] : people) ans += abs(a-b);
    cout << ans << '\n';

    return 0;
}
