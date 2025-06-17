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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


int dp[2][251][251][251];

typedef tuple<int, int, int, int, int> p5;
signed main()
{
    fast();

    rep(i, 2)rep(j, 251)rep(k, 251)rep(l, 251)dp[i][j][k][l] = inf;

    int d, n;
    cin >> d >> n;

    vector<p2> left;
    vector<p2> right;
    rep(i, n)
    {
        char c;
        int a, r;
        cin >> c >> a >> r;
        if (c == 'W') left.emplace_back(a, r);
        if (c == 'E') right.emplace_back(a, r);
    }
    
    priority_queue<p5> pq;
    pq.emplace(0, 0, 0, 0, 0);
    pq.emplace(0, 0, 0, 0, 1);

    while (sz(pq))
    {
        int t, ang, l, r, llast;
        tie(t, ang, l, r, llast) = pq.top();
        pq.pop();
        t = -t;
        if (dp[llast][l][r][ang] != inf)continue;
        //cout << ang << " " << l << " " << r << " " << llast << " = " << t << "\n";
        dp[llast][l][r][ang] = t;

        if (llast&&l<sz(left))
        {
            int nt = max(t, left[l].first);

            bool isangry = (left[l].first + left[l].second) < t;
            
            pq.emplace(-(nt + 3), ang + isangry, l + 1, r, 1);
            pq.emplace(-(nt + d), ang + isangry, l + 1, r, 0);

        }
        if (!llast&&r<sz(right))
        {
            int nt = max(t, right[r].first);
            bool isangry = (right[r].first + right[r].second) < t;
            pq.emplace(-(nt + 3), ang + isangry, l, r + 1, 0);
            pq.emplace(-(nt + d), ang + isangry, l, r + 1, 1);

        }
    }
    int ans = inf;
    rep(i, 2)rep(l, 251) if (dp[i][sz(left)][sz(right)][l] != inf)
    {
        
        ans = min(ans, l);
    }
    cout << ans;


    return 0;
}
