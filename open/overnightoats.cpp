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

    int n, x;
    cin >> n >> x;
    queue<int> oats;
    rep(i, n)
    {
        string action;
        cin >> action;
        if (action=="ADD")
        {
            oats.push(i);
        }
        else if (action=="EAT")
        {
            int t = oats.front();
            oats.pop();
            if (i - t > x)
            {
                cout << "ono..\n";
                return 0;
            }
        }
    }
    if (sz(oats)) cout << "ono..\n";
    else cout << "yay!\n";

    return 0;
}
