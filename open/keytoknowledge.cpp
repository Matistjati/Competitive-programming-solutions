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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<string> answers(n);
        vi num_right(n);
        rep(i, n)
        {
            cin >> answers[i] >> num_right[i];
        }

        if (m == 1)
        {
            auto get = [&](int i)
            {
                int ans = answers[i][0] - '0';
                if (num_right[i] == 0) ans = !ans;
                return ans;
            };
            bool consistent = 1;
            repp(i, 1, n) consistent &= get(i) == get(i - 1);
            if (consistent)
            {
                cout << get(0) << "\n";
            }
            else cout << "0 solutions\n";
            continue;
        }

        map<vi, pair<int, int>> occs;
        int split = m / 2 + 1;

        rep(mask, 1 << split)
        {
            vi dist(n);
            rep(i, n)
            {
                int agree = 0;
                rep(j, split) agree += ((mask & (1 << j)) > 0) == (answers[i][j] - '0');
                if (agree > num_right[i])
                {
                    goto end;
                }
                dist[i] = agree;
            }
            occs[dist].first++;
            occs[dist].second = mask;
        end:;
        }
        int ans = 0;
        int any = -1;
        rep(mask, 1 << (m - split))
        {
            vi dist(n);
            bool good = 1;
            rep(i, n)
            {
                int agree = 0;
                repp(j, split, m) agree += ((mask & (1 << (j - split))) > 0) == (answers[i][j] - '0');
                if (agree > num_right[i])
                {
                    good = 0;
                    break;
                }
                dist[i] = agree;
            }
            if (!good) continue;

            vi goal(n);
            rep(i, n) goal[i] = num_right[i] - dist[i];
            auto it = occs.find(goal);
            if (it != occs.end())
            {
                ans += it->second.first;
                any = it->second.second + (mask << split);
            }
        }

        if (ans == 1)
        {
            rep(i, m) cout << ((any & (1 << i)) > 0);
            cout << "\n";
        }
        else cout << ans << " solutions\n";
    }


    return 0;
}
