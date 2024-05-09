using namespace std;
#include <bits/stdc++.h>

#define rep(i,n) for(int i = 0; i < n; i++)
typedef pair<int, int> p2;
#define all(x) begin(x),end(x)

int main()
{
    int n, k;
    cin >> n >> k;
    vector<p2> intervals(n);
    rep(i, n) cin >> intervals[i].first >> intervals[i].second;
    sort(all(intervals), [](p2 a, p2 b)
        {
            if (a.second != b.second) return a.second < b.second;
    return a.first > b.first;
        });

    multiset<int> workers;


    int ans = 0;
    rep(i, n)
    {

        if (workers.size() && *begin(workers) <= intervals[i].first)
        {
            auto it = workers.upper_bound(intervals[i].first);
            //assert(it!=begin(workers));
            it = prev(it);
            //assert(*it<=intervals[i].first);
            workers.erase(it);
            workers.emplace(intervals[i].second);
            ans++;
        }
        else if (workers.size() < k)
        {
            workers.emplace(intervals[i].second);
            ans++;
        }
    }
    cout << ans << endl;
    return 0;

}