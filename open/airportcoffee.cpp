#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int l, a, b, t, r;
    cin >> l >> a >> b >> t >> r;
    int n;
    cin >> n;
    vector<double> positions(n);
    rep(i, n) cin >> positions[i];
    if (positions.empty() || positions.back() != l) positions.push_back(l);
    n = sz(positions);
    vector<double> dp(n);
    vi par(n);
    queue<int> waiting;
    double best_ran_out = inf;
    int best_ran_out_p = -inf;

    vi deleted(n);
    priority_queue<pair<double,int>> mid;
    queue<int> waiting_2;

    double best_normal = inf;
    int best_normal_p = inf;

    rep(i, n)
    {
        par[i] = -1;
        dp[i] = double(positions[i]) / a;

        if (best_normal+positions[i]/a<dp[i])
        {
            dp[i] = best_normal + positions[i] / a;
            par[i] = best_normal_p;
        }

        while (sz(waiting_2) && positions[i]-positions[waiting_2.front()]>=a*t)
        {
            int j = waiting_2.front();
            waiting_2.pop();
            waiting.push(j);
            mid.emplace(-(dp[j]+t+(-positions[j]-a*t)/b), j);
        }

        while (sz(waiting) && positions[i]-positions[waiting.front()]>=a*t+b*r)
        {
            int j = waiting.front();
            deleted[j] = 1;
            double c = dp[j] + r + (-positions[j] - r * b) / a;
            if (c<best_ran_out)
            {
                best_ran_out = c;
                best_ran_out_p = j;
            }
            waiting.pop();
        }

        while (sz(mid)&&deleted[mid.top().second])
        {
            mid.pop();
        }

        if (sz(mid))
        {
            double v = positions[i] / b -mid.top().first;
            if (v < dp[i])
            {
                dp[i] = v;
                par[i] = mid.top().second;
            }
        }

        double v = positions[i] / a + best_ran_out;
        if (v<dp[i])
        {
            dp[i] = v;
            par[i] = best_ran_out_p;
        }

        double bn = dp[i] - positions[i] / a;
        if (bn<best_normal)
        {
            best_normal = bn;
            best_normal_p = i;
        }

        waiting_2.push(i);
    }

    int u = n - 1;
    vi ans;
    while (u!=-1)
    {
        ans.push_back(u);
        u = par[u];
    }
    ans.erase(ans.begin());
    sort(all(ans));
    cout << sz(ans) << "\n";
    repe(v, ans) cout << v << " ";

    return 0;
}
