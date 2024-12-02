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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int numzero = 0;
    int numone = 0;
    repe(c, s) numzero += c == '0';
    repe(c, s) numone += c == '1';

    int bestans = 0;
    int num_placed = 0;
    vi breakpoints;
    rep(i, n)
    {

        

        if (s[i] == '1') numone--;
        if (s[i] == '0') numzero--;
        if (numone > numzero)
        {
            num_placed++;
            bestans += numone - numzero;
            breakpoints.push_back(numone - numzero);
        }

    }
    if (bestans<k)
    {
        cout << "-1\n";
        return;
    }
    sort(all(breakpoints));
    reverse(all(breakpoints));
    while (sz(breakpoints))
    {
        if (bestans - breakpoints.back() >= k)
        {
            bestans -= breakpoints.back();
            breakpoints.pop_back();
            num_placed--;
        }
        else break;
    }
    cout << num_placed+1 << "\n";
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
