#include <vector>
#include <algorithm>
#include <iostream>
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


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vi perm(n);
    for (ll& x : perm) cin >> x, x--;

    vector<vector<p2>> ans;
    // invariant: each interval's numbers are a permutation of the sorted final permutation in those positions
    vector<p2> intervals;
    intervals.emplace_back(0, n - 1);
    while (sz(intervals)) {
        vector<p2> new_intervals;

        vector<vector<p2>> rounds;

        auto first_one = [&](int l, int r, int pivot) {
            repp(i, l, r + 1) if (perm[i] >= pivot) return i;
            return -1LL;
        };

        auto do_reverse = [&](int l, int r, int depth) {
            while (depth >= sz(rounds)) rounds.emplace_back();
            rounds[depth].emplace_back(l, r);
            reverse(begin(perm) + l, begin(perm) + r + 1);
        };

        auto partition = [&](auto& self, int l, int r, int depth, int pivot) {
            if (l == r) return;
            int mid = (l + r) / 2;
            self(self, l, mid, depth + 1, pivot);
            self(self, mid + 1, r, depth + 1, pivot);

            int l_one = first_one(l, mid, pivot);
            int r_one = first_one(mid + 1, r, pivot);
            if (l_one == -1) return;
            if (r_one == -1) r_one = r + 1;
            do_reverse(l_one, r_one - 1, depth);
        };

        auto get_median = [&](int l, int r) {
            vi interval(begin(perm) + l, begin(perm) + r + 1);
            auto mid_el = begin(interval) + (sz(interval)+1) / 2;
            nth_element(begin(interval), mid_el, end(interval));
            return *mid_el;
        };

        for (auto [l, r] : intervals) {
            int mid = (l + r) / 2;

            int median = get_median(l,r);
            partition(partition, l, r, 0, median);
            if (l != mid) new_intervals.emplace_back(l, mid);
            if (mid + 1 != r) new_intervals.emplace_back(mid + 1, r);
        }
        reverse(all(rounds));
        for (auto r : rounds) ans.push_back(r);

        intervals = new_intervals;
    }

    cout << sz(ans) << "\n";
    repe(round, ans) {
        cout << sz(round) << '\n';
        repe(interval, round) {
            cout << interval.first + 1 << ' ' << interval.second + 1 << '\n';
        }
    }

    return 0;
}
