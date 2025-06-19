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

    int n;
    cin >> n;

    vi perm(n);
    rep(i, n)perm[i] = i;
    mt19937 rng(10);
    shuffle(all(perm), rng);
    vi unperm(n);
    rep(i, n) unperm[perm[i]] = i;
    function<int(int, int)> ask;
#if !_LOCAL
        ask = [perm](int i, int j)
            {
                cout << "? " << perm[i] + 1 << " " << perm[j] + 1 << endl;
                int res;
                cin >> res;
                return res;
            };
#else
        vi nums(n);
        repe(v, nums) cin >> v;
        ask = [nums, perm](int i, int j)
            {
                return min(nums[perm[i]], nums[perm[j]]);
            };
#endif


    if (n==2)
    {
        int v = ask(0, 1);
        cout << "! " << v << " " << v << endl;
        return 0;
    }

    vi top = { 0,1 };
    int m = ask(0,1);//second largest so far

    vi ans(n);
    repp(i, 2, n)
    {
        int v = ask(top[1], i);
        if (v<m)
        {
            ans[i] = v;
        }
        else
        {
            top.push_back(i);
            if (v==m)
            {
                ans[top[1]] = m;
                top.erase(top.begin() + 1);
                m = ask(top[0], top[1]);
            }
            else if (v>m)
            {
                ans[top[0]] = m;
                top.erase(top.begin());
                m = v;
            }
            else
            {
                ans[top.back()] = v;
                top.pop_back();
            }
        }
    }
    ans[top[0]] = m;
    ans[top[1]] = m;

    cout << "! ";
    rep(i, n) cout << ans[unperm[i]] << " ";

    return 0;
}
