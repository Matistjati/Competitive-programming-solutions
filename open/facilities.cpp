#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int n, T;
    cin >> n >> T;
    vector<p2> people(n);
    rep(i, n) cin >> people[i].first >> people[i].second;

    int ans = 0;
        priority_queue<tuple<int, int, int>> pq;
        rep(i, n)
        {
            pq.emplace(-people[i].first, 0, i);
        }

        int num_used = 0;
        while (1)
        {
            int t, i, pissing;
            tie(t, pissing, i) = pq.top();
            pq.pop();
            

            t = -t;
            if (t >= T)
            {
                break;
            }
            if (!pissing)
            {
                num_used++;
                ans = max(ans, num_used);
                pq.emplace(-(t + people[i].second), 1, i);
            }
            else
            {
                num_used--;
                pq.emplace(-(t + people[i].first), 0, i);

            }
        }


    cout << ans;

    return 0;
}
