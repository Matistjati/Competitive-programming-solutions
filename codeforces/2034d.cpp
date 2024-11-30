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
    vi nums(n);
    rep(i, n) cin >> nums[i];
    int zerocnt = 0;
    int onecnt = 0;
    int twocnt = 0;

    set<int> occ[3];
    rep(i, n)
    {
        occ[nums[i]].insert(i);
        if (nums[i] == 0) zerocnt++;
        if (nums[i] == 1) onecnt++;
        if (nums[i] == 2) twocnt++;
    }

    vector<p2> moves;
    auto swop = [&](int i, int j)
        {
            moves.emplace_back(i, j);

            int a = nums[i];
            int b = nums[j];
            occ[a].erase(i);
            occ[b].erase(j);
            occ[b].insert(i);
            occ[a].insert(j);

            swap(nums[i], nums[j]);
        };

    // [0, zerocnt-1] is all zeros
    
    rep(i, zerocnt)
    {
        if (nums[i]==1)
        {
            int zeroind = *prev(end(occ[0]));
            swop(i, zeroind);
            assert(nums[i] == 0);
        }
    }
    rep(i, zerocnt)
    {
        if (nums[i]==2)
        {
            int oneind = *prev(end(occ[1]));
            swop(i, oneind);
            assert(nums[i] == 1);
            int zeroind = *prev(end(occ[0]));
            swop(i, zeroind);
            assert(nums[i] == 0);
        }
    }
    repp(i, zerocnt, zerocnt + onecnt)
    {
        if (nums[i]==2)
        {
            int oneind = *prev(end(occ[1]));
            swop(i, oneind);
            assert(nums[i] == 1);
        }
    }

    cout << sz(moves) << "\n";
    repe(m, moves)
    {
        cout << m.first + 1 << " " << m.second + 1 << "\n";
    }
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
