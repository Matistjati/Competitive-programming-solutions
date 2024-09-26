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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

bool ask(string s)
{
    cout << "? " << s << endl;
    int resp;
    cin >> resp;
    return resp;
}

void solve()
{
    int n;
    cin >> n;

    mt19937 rng((int)malloc(10));
    uniform_int_distribution<int> dist(0, 1);
    string s = "";
    while (true)
    {
        char c = (dist(rng) % 2 ? '0' : '1');
        s += c;
        if (ask(s)==0)
        {
            s.pop_back();
            s += (c == '0' ? '1' : '0');
            if (ask(s)==0)
            {
                s.pop_back();
                break;
            }
        }
        if (sz(s)>=n)
        {
            break;
        }
    }
    int it = n - sz(s);
    rep(i, it)
    {
        char c = (dist(rng) % 2 ? '0' : '1');
        s = c + s;
        if (ask(s) == 0)
        {
            s.erase(s.begin());
            s = (c == '0' ? '1' : '0') + s;
        }
    }
    cout << "! " << s << endl;
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
