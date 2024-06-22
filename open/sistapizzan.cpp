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
    vi nums(n);
    rep(i, n) cin >> nums[i];
    if (n==1)
    {
        cout << (nums[0] % 2 == 0 ? "Ja" : "Nej");
    }
    else if (n==2)
    {
        bool wina = nums[0] % 2 == 1;
        bool winb = nums[1] % 2 == 1;
        if (wina||winb)
        {
            cout << "Ja";
        }
        else
        {
            cout << "Nej";
        }
    }
    else if (n==3)
    {
        bool wina = nums[0] % 2 == 0;
        bool winb = nums[1] % 2 == 0;
        bool winc = nums[2] % 2 == 0;
        if (wina || winb || winc)
        {
            cout << "Ja";
        }
        else
        {
            cout << "Nej";
        }
    }

    return 0;
}
