// overcomplicated...
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

vi cube;
vi cylinder;
int dp[2][105][105];
tuple<int,int,int> to[2][105][105];
int choice[2][105][105];
int longest(int cu, int cy, bool above)
{
    int& v = dp[above][cu][cy];
    if (v != -1) return v;
    tuple<int, int, int>& c = to[above][cu][cy];
    int& cc = choice[above][cu][cy];
    int ret = 0;

    if (above)
    {
        if (cu+1<sz(cube))
        {
            int x = 1+longest(cu + 1, cy, above);
            if (x>ret)
            {
                ret = x;
                c = { cu + 1, cy, above };
                cc = 1;
            }
        }
        auto it = lower_bound(all(cylinder), ceil(cube[cu]/sqrt(2)));
        if (it != cylinder.end())
        {
            if (*it == 0) it = next(it);
            if (it!=cylinder.end())
            {
                int x = 1+longest(cu, it-begin(cylinder), !above);
                if (x > ret)
                {
                    ret = x;
                    c = { cu, it - begin(cylinder), !above };
                    cc = 2;
                }
            }
        }
    }
    else
    {
        if (cy + 1 < sz(cylinder))
        {
            int x = 1+longest(cu, cy+1, above);
            if (x > ret)
            {
                ret = x;
                c = { cu, cy + 1, above };
                cc = 3;
            }
        }

        auto it = lower_bound(all(cube), cylinder[cy] * 2);
        if (it != cube.end())
        {
            if (*it == 0) it = next(it);
            if (it != cube.end())
            {
                int x = 1 + longest(it - begin(cube), cy, !above);
                if (x > ret)
                {
                    ret = x;
                    c = { it - begin(cube), cy, !above };
                    cc = 4;
                }
            }
        }
    }


    return v = ret;
}

signed main()
{
    fast();

    memset(dp, -1, sizeof(dp));

    int n;
    cin >> n;
    
    rep(i, n)
    {
        string t;
        int r;
        cin >> t >> r;
        if (t == "cube") cube.emplace_back(r);
        else cylinder.emplace_back(r);
    }
    sort(all(cube));
    sort(all(cylinder));
    cube.insert(cube.begin(), 0);
    cylinder.insert(cylinder.begin(), 0);

    if (longest(0, 0, 1) != sz(cube) + sz(cylinder) - 2)
    {
        cout << "impossible";
        return 0;
    }
    tuple<int, int, int> state = { 0,0,1 };
    vector<pair<string,int>> ans;
    while (1)
    {
        int a, b, above;
        tie(a, b, above) = state;
        if (dp[above][a][b] == 0) break;
        if (choice[above][a][b]==1)
        {
            ans.emplace_back("cube", cube[a + 1]);
        }
        else if (choice[above][a][b] == 2)
        {
            ans.emplace_back("cylinder", cylinder[get<1>(to[above][a][b])]);
        }
        else if (choice[above][a][b] == 3)
        {
            ans.emplace_back("cylinder", cylinder[b+1]);
        }
        else if (choice[above][a][b] == 4)
        {
            ans.emplace_back("cube", cube[get<0>(to[above][a][b])]);
        }

        state = to[above][a][b];
    }
    repe(u, ans) cout << u.first << " " << u.second << "\n";

    return 0;
}
