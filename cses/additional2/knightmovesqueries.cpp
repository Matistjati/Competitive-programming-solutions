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

int knightDistance(int x, int y) {
    x = abs(x), y = abs(y);
    if (x < y) swap(x, y);
    if (x == 1 && y == 0) return 3;
    if ((x == 2 && y == 2) || (x == 1 && y == 1)) return 4;
    int d = max((x + 1) / 2, (x + y + 2) / 3);
    return d % 2 != (x + y) % 2 ? d + 1 : d;
}

signed main()
{
    fast();

    int n;
    cin >> n;

    while (n--)
    {
        int x, y;
        cin >> x >> y;
        x--; y--;
        cout << knightDistance(x, y) << "\n";
    }

    return 0;
}
