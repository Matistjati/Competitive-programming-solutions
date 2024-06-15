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
#define __builtin_popcountll popcount
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int n;
    cin >> n;
    vvi taken(26, vi(26, (1<<26)-1));
    int used[26][26][26];
    memset(used, 0, sizeof(used));
    rep(_, n)
    {
        string namestr;
        cin >> namestr;
        
        rep(i, sz(namestr)) namestr[i] = toupper(namestr[i]);
        vi name(sz(namestr));
        rep(i, sz(namestr)) name[i] = namestr[i] - 'A';
        vi first(26,-1);
        vi active(26,-1);
        rep(i, sz(name))
        {
            if (first[name[i]] == -1) first[name[i]] = i;
        }
        vvi leftestpos(sz(name));
        vi leftest(26, inf);
        for (int j = sz(name) - 1; j >= 0; j--)
        {
            leftestpos[j] = leftest;
            leftest[name[j]] = j;
        }
        
        tuple<int, int, int> best = { inf,inf,inf };
        for (int j = sz(name)-1; j >= 0; j--)
        {
            int m = name[j];
            rep(i, 26)
            {
                if (first[i] == -1 || first[i] >= j) continue;
                if (first[i] > get<0>(best)) continue;

                int r = inf;
                rep(k, 26)
                {
                    if (used[i][m][k]) continue;
                    r = min(r, leftestpos[j][k]);
                }
                if (r == inf) continue;
                tuple<int, int, int> cand = { first[i], j, r };
                best = min(best, cand);
            }
        }
        if (get<0>(best) != inf)
        {
            int a, b, c;
            tie(a, b, c) = best;
            used[name[a]][name[b]][name[c]] = 1;
            cout << namestr[a] << namestr[b] << namestr[c] << "\n";
        }
        else cout << ":(\n";
        
        
    }

    return 0;
}
