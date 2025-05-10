// FUCK THIS PROBLEM
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


bitset<int(1e9)> seen;

signed main()
{
    fast();

    seen[0] = 1;
    int time = 0;
    while (time < int(1e9))
    {
        time += 3;
        seen[time / 2] = 1;
    }

    int q;
    cin >> q;
    while (q--)
    {
        string x;
        cin >> x;
        string nx;
        repe(c, x) if (c != '.') nx.push_back(c);
        int k = stoi(nx);
        if (seen[k])
        {
            cout << "VALID\n";
        }
        else cout << "IMPOSSIBLE\n";
    }

    return 0;
}

