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


    int _;
    cin >> _;
    string s;
    cin >> s;

    vi cnt(4);
    repe(c, s)
    {
        if (c == 'N') cnt[0]++;
        if (c == 'W') cnt[1]++;
        if (c == 'S') cnt[2]++;
        if (c == 'E') cnt[3]++;
    }

    int ans = 0;

    auto reduce = [&](int ind)
        {
            while (cnt[ind] > 10)
            {
                cnt[ind] -= 2;
                ans += 4 - ind;
            }
        };
    reduce(1);
    reduce(2);
    reduce(3);

    cnt[0] = min(10LL, cnt[0]);
    int t = accumulate(all(cnt), 0);
    queue<tuple<int, int, int, int>> q;
    q.emplace(0, cnt[1], cnt[2], cnt[3]);
    int ans2 = inf;
    set<tuple<int, int, int>> vis;
    while (sz(q))
    {
        auto [d, w, s, e] = q.front();
        q.pop();

        tuple<int, int, int> st = { w,s,e };
        if (vis.count(st)) continue;
        vis.insert(st);
        if (w + s + e == 0)
        {
            ans2 = d;
            break;
        }

        int north = t - w - s - e;
        rep(i, 4) rep(j, 4)
        {
            vi s2 = { north,w,s,e };
            s2[i]--;
            s2[j]--;
            if (s2[i] < 0 || s2[j] < 0) continue;
            s2[(i + 1) % 4]++;
            s2[(j + 1) % 4]++;
            q.emplace(d + 1, s2[1], s2[2], s2[3]);
        }
    }

    if (ans2 == inf)
    {
        cout << -1;
    }
    else cout << ans + ans2;

    return 0;
}
