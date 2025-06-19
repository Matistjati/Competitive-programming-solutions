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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

signed main()
{
    fast();

    int n, m, c;
    cin >> n >> m >> c;
    vi nums(n);
    repe(v, nums) cin >> v;

    deque<p2> minq;
    deque<p2> maxq;

    int cnt = 0;

    auto add = [](deque<p2>& q, int i, int v)
        {
            while (sz(q) && q.back().second <= v) q.pop_back();
            q.emplace_back(i, v);
        };

    auto query = [m](deque<p2>&q, int i)
        {
            while (q.front().first + m <= i) q.pop_front();
            return q.front().second;
        };

    rep(i, m) add(minq, i, -nums[i]);
    rep(i, m) add(maxq, i, nums[i]);

    auto check = [&](int i)
        {
            if (query(maxq, i) + query(minq, i) <= c)
            {
                cout << i-m+2 << "\n";
                cnt++;
            }
        };
    check(m - 1);

    repp(i, m, n)
    {
        add(minq, i, -nums[i]);
        add(maxq, i, nums[i]);
        check(i);
    }

    if (cnt == 0) cout << "NONE";

    return 0;
}
