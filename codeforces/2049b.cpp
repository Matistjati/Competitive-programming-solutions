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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<vector<p2>> intervals(n);
    rep(i, n)
    {
        if (s[i]=='p')
        {
            rep(j, i + 1)
            {
                intervals[j].push_back(p2(0, i));
            }
        }
        if (s[i]=='s')
        {
            int start = 0;
            repp(j, i, n)
            {
                intervals[start].push_back(p2(i, n-1));
                start++;
            }
        }
    }
    vector<p2> merged(n, p2(0, n - 1));
    rep(i, n)
    {
        repe(smol, intervals[i])
        {
            p2 large = merged[i];
            large.first = max(large.first, smol.first);
            large.second = min(large.second, smol.second);

            merged[i] = large;
        }
        if (merged[i].first>merged[i].second)
        {
            cout << "NO\n";
            return;
        }
    }
    sort(all(merged));

    priority_queue<int> active;
    int idx = 0;
    rep(i, n)
    {
        while (idx < n && merged[idx].first <= i)
        {
            active.push(-merged[idx].second);
            idx++;
        }

        if (active.empty())
        {
            cout << "NO\n";
            return;
        }
        if (-active.top() < i)
        {
            cout << "NO\n";
            return;
        }
        active.pop();
    }


    cout << "YES\n";

}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
