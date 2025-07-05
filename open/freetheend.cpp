#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
//const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }


int s, d, p;
int hits_req;
char dp[2001][1001][35];
void outcome(int hp, int sword, int potions)
{
    if (dp[hp+10][sword][potions] == 1) return;
    dp[hp+10][sword][potions] = 1;
    if (hp < 0) return;
    if (sword >= hits_req) return;

    rep(a, 5)
    {
        rep(b, 5)
        {
            if (a + b > 4) continue;
            if (sword + a > s) continue;
            if (potions + b > p) continue;
            int newhp = hp + b * 8;
            if (sword + a < hits_req) newhp -= 10;
            newhp = min(newhp, 20);
            outcome(newhp, sword + a, potions + b);
        }
    }

}

signed main()
{
    fast();

    memset(dp, 0, sizeof(dp));
    cin >> s >> d >> p;
    hits_req = (d + 3) / 4;
    //outcome(20, 0, 0);

    bool wins = false;
    int max_hits = 0;
    dp[0][0][30] = 1;
    rep(sword, s+1) rep(potion, p+1)
    {
        repp(hp, 1, 25)
        {
            if (!dp[sword][potion][hp+10]) continue;
            rep(a, 5)
            {
                if (sword + a > s) continue;
                rep(b, 5)
                {
                    if (a + b > 4) continue;
                    if (potion + b > p) continue;
                    int newhp = hp + b * 8;
                    if (sword < hits_req) newhp -= 10;
                    newhp = min(newhp, 20);
                    dp[sword + a][potion + b][newhp+10] = 1;
                }
            }
        }
    }

    rep(d, 2001) rep(p, 1001) rep(h, 35)
    {
        if (dp[d][p][h] && d >= hits_req) wins = 1;
        if (dp[d][p][h])
        {
            max_hits = max(max_hits, d);
        }
    }
    if (wins)
    {
        cout << "Steve wins\n";
    }
    else if (max_hits == s)
    {
        cout << "broken sword\n";
    }
    else cout << "not enough potions\n";

    return 0;
}
