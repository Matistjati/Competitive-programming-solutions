#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

p2 out = p2(-1, -1);
const ll MAYBE = 0;
const ll NO = 1;
const ll YES = 2;

vi dirmap(127);

void filldirmap()
{
    dirmap['S'] = 2;
    dirmap['E'] = 0;
    dirmap['W'] = 1;
    dirmap['N'] = 3;
}

ll M;
inline ll h(ll f, ll s, ll d)
{
    return f * 4 * M + 4 * s + d;
}

inline ll h2(ll r, ll c)
{
    return r * M + c;
}

inline ll h2(p2 p)
{
    return p.first * M + p.second;
}

ll findnext(ll u, ll dir, vi& jump, string& grid)
{
    if (u == inf) return u;
    if (grid[u] != '.')
    {
        return u;
    }
    return jump[u * 4 + dir] = findnext(jump[u * 4 + dir], dir, jump, grid);

}

p2 dfs(ll u, string& grid, vi& jump, vi& canbemoved)
{
    ll ans = 0;
    while (true)
    {
        if (canbemoved[u] == YES) return p2(ans, YES);
        if (canbemoved[u] == NO) return p2(ans, NO);
        canbemoved[u] = NO;
        p2 ret = p2(ans, 0);

        ll next = findnext(jump[u * 4 + dirmap[grid[u]]], dirmap[grid[u]], jump, grid);

        if (next == inf)
        {
            ret = p2(ans + 1, YES);
            canbemoved[u] = YES;
            grid[u] = '.';
            return ret;
        }
        else
        {
            if (canbemoved[next] == NO)
            {
                canbemoved[u] = NO;
                return p2(ans, NO);
            }
            p2 r = dfs(next, grid, jump, canbemoved);
            ans += r.first;
            if (r.second == NO)
            {
                canbemoved[u] = NO;
                return p2(ans, NO);
            }
        }
        canbemoved[u] = MAYBE;
    }
}

vector<p2> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
ll solve(vector<string>& grid)
{
    ll n = grid.size();
    ll m = grid[0].size();
    M = m;
    filldirmap();

    ll ans = 0;
    vi canbemoved(n * m, MAYBE);
    vi jump(n * m * 4);

    string grid2;

    rep(i, n)
    {
        rep(j, m)
        {
            grid2.push_back(grid[i][j]);
            rep(d, 4)
            {
                p2 p = p2(i+dirs[d].first, j+dirs[d].second);
                if (p.first < 0 || p.first >= n || p.second < 0 || p.second >= m)
                {
                    jump[h(i, j, d)] = inf;
                }
                else
                {
                    jump[h(i, j, d)] = h2(p2(i+dirs[d].first, j+dirs[d].second));
                }
            }
        }
    }

    rep(i, n) rep(j, m)
    {
        ll u = h2(i, j);
        if (grid2[u] == '.') continue;
        if (canbemoved[u] != MAYBE) continue;
        ans += dfs(h2(i, j), grid2, jump, canbemoved).first;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto& v : grid) cin >> v;
    cout << solve(grid) << '\n';

    return 0;
}
