#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

signed main()
{
    fast();

    int n;
    cin >> n;
    vi nums(n - 1);
    repe(v, nums) cin >> v;
    map<int, int> occs;
    repe(v, nums) occs[v]++;
    set<int> keys(all(nums));
    repe(v, keys) occs[v]--;
    vi repl;
    occs[1]++;
    repe(o, occs) rep(i, o.second) repl.push_back(o.first);
    nums = repl;
    priority_queue<int> avail;
    vi ans(n, -1);
    vi keyv(all(keys));
    reverse(all(keyv));
    ans[keyv[0]] = keyv[0];
    rep(i, sz(keyv) - 1)
    {
        ans[keyv[i]-1] = keyv[i + 1];
    }

    int j = 0;
    repp(i, 1, n)
    {
        if (ans[i] != -1) continue;
        while (j < sz(nums) && nums[j] <= i)
        {
            avail.push(nums[j++]);
        }
        ans[i] = avail.top();
        avail.pop();
    }

    repp(i, 1, n) cout << ans[i] << " ";

    return 0;
}
