using namespace std;
#include <bits/stdc++.h>

#define rep(i,n) for(int i = 0; i < n; i++)
typedef pair<int, int> p2;
#define all(x) begin(x),end(x)

bitset<10010 * 10010> bset;
int main()
{
    int g;
    cin >> g;
    vector<p2> goblins(g);
    rep(i, g) cin >> goblins[i].first >> goblins[i].second;

    vector<vector<p2>> offsets(101);
    for (int r = 1; r <= 100; r++)
    {
        rep(dx, r + 1)
        {
            rep(dy, r + 1)
            {
                if (dx * dx + dy * dy <= r * r)
                {
                    offsets[r].emplace_back(dx, dy);
                }
            }
        }
    }

    int m;
    cin >> m;
    rep(_, m)
    {
        int x, y, r;
        cin >> x >> y >> r;
        for (auto off : offsets[r])
        {
            if (x + off.first <= 10000 && y + off.second <= 10000) bset[(x + off.first) * 10001 + y + off.second] = 1;
            if (x - off.first >= 0 && y + off.second <= 10000) bset[(x - off.first) * 10001 + y + off.second] = 1;
            if (x + off.first <= 10000 && y - off.second >= 0) bset[(x + off.first) * 10001 + y - off.second] = 1;
            if (x - off.first >= 0 && y - off.second >= 0) bset[(x - off.first) * 10001 + y - off.second] = 1;
        }
    }

    int ans = 0;
    for (auto g : goblins)
    {
        ans += bset[g.first * 10001 + g.second];
    }
    cout << g - ans << "\n";

    return 0;
}