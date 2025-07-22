#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

#define rep(i, b) for(ll i = 0; i < (b); i++)
#define repp(i, a, b) for(ll i = a; i < (b); i++)
#define repe(i,arr) for (auto& i : arr)
#define all(x) begin(x), end(x)
#define sz(x) ((ll)(x).size())
typedef pair<ll, ll> p2;
typedef vector<ll> vi;
typedef vector<vi> vvi;


char vis[15][1 << 15];
void dp(ll mask, ll i, vi& goal, vi& blocks, vvi& construction)
{
    if (i==sz(goal))
    {
        repe(c, construction)
        {
            cout << sz(c) << " ";
            repe(b, c) cout << b+1 << " ";
            cout << "\n";
        }
        exit(0);
    }
    if (vis[i][mask]) return;
    vis[i][mask] = 1;

    for (ll s = mask; s < (1<<sz(blocks)); s = (s + 1) | mask)
    {
        ll newones = s ^ mask;
        ll sum = 0;
        rep(i, sz(blocks))
        {
            if (newones &(1<<i))
            {
                sum += blocks[i];
            }
        }
        if (sum==goal[i])
        {
            rep(j, sz(blocks))
            {
                if (newones & (1 << j))
                {
                    construction[i].push_back(j);
                }
            }
            dp(s, i + 1, goal, blocks, construction);
            construction[i].clear();
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n, s;
    cin >> n >> s;

    vi material(n), goal(s);
    repe(v, material) cin >> v;
    repe(v, goal) cin >> v;
    vvi construction(s);
    dp(0, 0, goal, material, construction);
    cout << "-1";

    return 0;
}
