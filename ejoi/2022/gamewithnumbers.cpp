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

vi moves;
int play(vi nums, int pos)
{
    if (sz(nums)==0)
    {
        return 0;
    }
    if (pos==sz(moves))
    {
        return accumulate(all(nums), 0LL)*(sz(moves)%2==0?1:-1);
    }

    vi divisible;
    vi not_divisible;
    repe(num, nums)
    {
        if (num % moves[pos] == 0) divisible.push_back(num);
        else not_divisible.push_back(num);
    }
    return -max(play(divisible, pos + 1), play(not_divisible, pos + 1));
}

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;
    vi nums(n);
    rep(i, n) cin >> nums[i];
    moves.resize(m);
    rep(i, m) cin >> moves[i];
    
    if (m>35)
    {
        cout << 0;
    }
    else cout << play(nums, 0);

    return 0;
}
