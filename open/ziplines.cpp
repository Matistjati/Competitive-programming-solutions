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
#define sz(x) ((int)(x).size())

ll dfs(int u, vi& dp, vvi& adj)
{
    ll& v = dp[u];
    if (v != -1) return v;

    ll ret = 0;
    repe(e, adj[u]) ret = max(ret, 1 + dfs(e, dp, adj));

    return v = ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vi nums(n);
    repe(v, nums) cin >> v;

    auto get_edges = [&]()
    {
        vector<p2> edg;
        deque<p2> heights;
        rep(i, n)
        {
            auto it_me = lower_bound(all(heights), p2(nums[i], -inf));
            
            auto it = upper_bound(all(heights), p2(nums[i], inf));
            if ((it_me==end(heights)||it_me->first!=nums[i]) && it != end(heights))
            {
                edg.emplace_back(i, it->second);
            }
            while (sz(heights) && heights[0].first <= nums[i]) heights.pop_front();
            heights.emplace_front(nums[i], i);
        }
        return edg;
    };

    vector<p2> ledges = get_edges();
    reverse(all(nums));
    vector<p2> redges = get_edges();
    vvi adj(n);
    for (auto [a, b] : ledges)
    {
        adj[b].push_back(a);
    }
    for (auto [a, b] : redges)
    {
        a = n - a-1;
        b = n - b-1;
        adj[b].push_back(a);
    }
    vi dp(n, -1);
    ll ans = 0;
    rep(i, n) ans = max(ans, dfs(i, dp, adj));
    cout << ans << '\n';

    return 0;
}
