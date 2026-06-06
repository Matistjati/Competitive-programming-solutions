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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,k;
    cin >> n >> k;
    vector<pair<int,int>> jobs(n);
    rep(i,n) {
        int l,r;
        cin >> l >> r;
        r+=l;
        jobs[i]={l,r};
    }
    sort(all(jobs), [](pair<int,int> a, pair<int,int> b) {
        return a.second < b.second;
    });

    auto solve = [&](int n_machines) {
        int completed = 0;
        multiset<int> free_at;
        rep(i,n_machines) free_at.insert(i);

        for (auto [start,deadline] : jobs) {
            auto it = free_at.upper_bound(start);
            if (it!=free_at.begin()) {
                it=prev(it);
                completed++;
                int t = *it;
                free_at.erase(it);
                free_at.insert(deadline);
            }
        }

        return completed;
    };

    int lo = -1;
    int hi = n+1;
    while (lo+1<hi) {
        int mid = (lo+hi)/2;
        int completed = solve(mid);
        if (completed >= k) hi=mid;
        else lo = mid;
    }
    cout << hi << '\n';

    return 0;
}
