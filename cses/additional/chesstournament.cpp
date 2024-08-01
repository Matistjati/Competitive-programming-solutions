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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int n;
    cin >> n;
    priority_queue<p2> pq;
    rep(i, n)
    {
        int v;
        cin >> v;
        if (!v) continue;
        pq.emplace(v, i+1);
    }

    vector<p2> ans;
    while (sz(pq))
    {
        p2 a = pq.top();
        pq.pop();

        vector<p2> out;
        while (a.first)
        {
            if (pq.empty())
            {
                cout << "IMPOSSIBLE";
                return 0;
            }
            a.first--;
            p2 b = pq.top();
            pq.pop();
            b.first--;
            ans.emplace_back(a.second, b.second);
            if (b.first) out.push_back(b);
        }
        repe(o, out) pq.emplace(o);
    }

    cout << sz(ans) << "\n";
    rep(i, sz(ans))
    {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }

    return 0;
}
