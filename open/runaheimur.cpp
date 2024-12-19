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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


typedef array<char, 100> state;

ll hashstate(state& x)
{
    ll ret = 0;
    rep(i, 100)
    {
        ret = (ret * 131 + x[i]);
    }
    return ret;
}

// A* to solve the 3x3 in the end
struct comp
{
    bool operator()(tuple<ll, ll, state>& l, tuple<ll, ll, state>& r)
    {
        return get<0>(l) > get<0>(r);
    }
};

int32_t main()
{
    fast();

    int r, c;
    cin >> r >> c;

    array<char, 100> puzzle;
    rep(i, 100) puzzle[i] = -2;
    rep(i, r) rep(j, c)
    {
        int temp;
        cin >> temp;
        puzzle[i * c + j] = temp - 1;
    }

    auto inversions = [&]()
        {
            int inv = 0;
            rep(i, r * c) // y
            {
                rep(j, i) // x
                {
                    inv += puzzle[j] > puzzle[i];
                }
            }
            return inv % 2;
        };

    if (inversions() == 1)
    {
        cout << "impossible";
        return 0;
    }

    int fixedrows = 0;
    int fixedcols = 0;

    vi blocked(r * c);
    string ans = "";
    map<p2, char> dirtoc;
    dirtoc[p2(0, 1)] = 'L';
    dirtoc[p2(0, -1)] = 'R';
    dirtoc[p2(1, 0)] = 'U';
    dirtoc[p2(-1, 0)] = 'D';
    p2 emptyspace = p2(r - 1, c - 1);
    auto at = [&](int i, int j)
        {
            return puzzle[i * c + j];
        };
    auto isblocked = [&](int i, int j)
        {
            return blocked[i * c + j];
        };
    auto sw = [&](int dr, int dc)
        {
            ans += dirtoc[p2(dr, dc)];
            p2 np = p2(emptyspace.first + dr, emptyspace.second + dc);
            swap(puzzle[emptyspace.first * c + emptyspace.second], puzzle[np.first * c + np.second]);
            emptyspace = np;
        };


    auto toint = [&](p2 x)
        {
            return x.first * c + x.second;
        };
    auto top2 = [&](int x)
        {
            return p2(x / c, x % c);
        };
    vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

    auto moveto = [&](p2 goal)
        {
            vi par(r * c, -1);
            par[toint(emptyspace)] = -2;

            queue<int> q;
            q.emplace(toint(emptyspace));
            while (sz(q))
            {
                int u = q.front();
                q.pop();
                if (blocked[u]) continue;
                repe(dir, dirs)
                {
                    p2 np = p2(top2(u).first + dir.first, top2(u).second + dir.second);
                    if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= c) continue;
                    if (par[toint(np)] == -1)
                    {
                        par[toint(np)] = u;
                        q.emplace(toint(np));
                    }
                }
            }

            vi moves;
            int u = toint(goal);
            while (u != -2)
            {
                moves.push_back(u);
                assert(u != -1);
                u = par[u];
            }
            reverse(all(moves));
            rep(i, sz(moves) - 1)
            {
                int curr = moves[i];
                int nxt = moves[i + 1];
                if (curr + 1 == nxt)
                {
                    ans += 'L';
                }
                else if (curr - 1 == nxt)
                {
                    ans += 'R';
                }
                else if (curr + c == nxt)
                {
                    ans += 'U';
                }
                else if (curr - c == nxt)
                {
                    ans += 'D';
                }
                else assert(0);
                swap(puzzle[curr], puzzle[nxt]);
            }
            emptyspace = goal;
        };
    auto find = [&](int x)
        {
            rep(i, r * c) if (puzzle[i] == x) return i;
            assert(0);
        };




    auto movetile = [&](int tofix, p2 target)
        {
            while (find(tofix) != toint(target))
            {
                p2 pos = top2(find(tofix));
                if (pos.second < target.second)
                {
                    blocked[toint(pos)] = 1;
                    moveto(p2(pos.first, pos.second + 1));
                    sw(0, -1);
                    blocked[toint(pos)] = 0;
                    continue;
                }
                if (pos.first > target.first)
                {
                    blocked[toint(pos)] = 1;
                    moveto(p2(pos.first - 1, pos.second));
                    sw(1, 0);
                    blocked[toint(pos)] = 0;
                    continue;
                }
                if (pos.first < target.first)
                {
                    blocked[toint(pos)] = 1;
                    moveto(p2(pos.first + 1, pos.second));
                    sw(-1, 0);
                    blocked[toint(pos)] = 0;
                    continue;
                }
                if (pos.second > target.second)
                {
                    blocked[toint(pos)] = 1;
                    moveto(p2(pos.first, pos.second - 1));
                    sw(0, 1);
                    blocked[toint(pos)] = 0;
                    continue;
                }
            }
        };

    auto fix_row = [&]()
        {
            repp(i, fixedcols, c - 2)
            {
                int tofix = fixedrows * c + i;
                movetile(tofix, p2(fixedrows, i));
                blocked[toint(p2(fixedrows, i))] = 1;
            }
            movetile(fixedrows * c + c - 1, p2(fixedrows, c - 2));
            if (at(fixedrows, c - 1) == fixedrows * c + c - 2)
            {
                blocked[fixedrows * c + c - 1] = 1;
                blocked[fixedrows * c + c - 2] = 1;
                moveto(p2(fixedrows + 1, c - 2));
                string moves = "DLUURDDLURDLUURDLURDLRDLU";
                repe(c, moves)
                {
                    if (c == 'U')
                    {
                        sw(1, 0);
                    }
                    if (c == 'D')
                    {
                        sw(-1, 0);
                    }
                    if (c == 'L')
                    {
                        sw(0, 1);
                    }
                    if (c == 'R')
                    {
                        sw(0, -1);
                    }
                }
                return;
            }
            blocked[fixedrows * c + c - 2] = 1;
            movetile(fixedrows * c + c - 2, p2(fixedrows + 1, c - 2));
            blocked[(fixedrows + 1) * c + c - 2] = 1;
            moveto(p2(fixedrows, c - 1));
            blocked[fixedrows * c + c - 2] = 0;
            blocked[(fixedrows + 1) * c + c - 2] = 0;
            sw(0, -1);
            sw(1, 0);
        };
    auto fix_col = [&]()
        {
            repp(i, fixedrows, r - 2)
            {
                int tofix = i * c + fixedcols;
                movetile(tofix, p2(i, fixedcols));
                blocked[toint(p2(i, fixedcols))] = 1;
            }
            movetile(toint(p2(r - 1, fixedcols)), p2(r - 2, fixedcols));

            int a = at(r - 1, fixedcols + 1);
            int b = toint(p2(r - 2, fixedcols));
            if (emptyspace == p2(r - 1, fixedcols) && a == b)
            {
                sw(0, 1);
                sw(-1, 0);
            }

            int tob = puzzle[toint(p2(r - 1, fixedcols))];
            if (tob == toint(p2(r - 2, fixedcols)))
            {
                moveto(p2(r - 2, fixedcols + 1));
                string moves = "URDLULDRURDLURDLLURRDL";
                repe(c, moves)
                {
                    if (c == 'U')
                    {
                        sw(1, 0);
                    }
                    if (c == 'D')
                    {
                        sw(-1, 0);
                    }
                    if (c == 'L')
                    {
                        sw(0, 1);
                    }
                    if (c == 'R')
                    {
                        sw(0, -1);
                    }
                }
                blocked[toint(p2(r - 2, fixedcols))] = 1;
                blocked[toint(p2(r - 1, fixedcols))] = 1;
                return;
            }
            blocked[toint(p2(r - 2, fixedcols))] = 1;
            movetile(toint(p2(r - 2, fixedcols)), p2(r - 2, fixedcols + 1));
            blocked[toint(p2(r - 2, fixedcols + 1))] = 1;

            moveto(p2(r - 1, fixedcols));

            blocked[toint(p2(r - 2, fixedcols + 1))] = 0;

            sw(-1, 0);
            sw(0, 1);
            blocked[toint(p2(r - 1, fixedcols))] = 1;
        };

    while (r - fixedrows > 3)
    {
        fix_row();
        fixedrows++;
    }

    while (c - fixedcols > 3)
    {
        fix_col();
        fixedcols++;
    }
    
    auto eval = [&](state& s)
        {
            int ret = 0;
            for (int i = r - 1; i >= max(0LL, r - 3); i--)
            {
                for (int j = c - 1; j >= max(0LL, c - 3); j--)
                {
                    int loc;
                    rep(k, 100) if (s[k] == i*c+j)
                    {
                        loc = k;
                        break;
                    }
                    p2 rp = top2(loc);
                    ret += abs(i - rp.first) + abs(j - rp.second);
                }
            }
            return ret;
        };

    state target;
    state neutral;
    rep(i, 100) target[i] = neutral[i] = -2;
    rep(i, r * c) neutral[i] = -2;
    rep(i, r * c) target[i] = i;
    priority_queue<tuple<ll, ll, state>, vector<tuple<ll, ll, state>>, comp> q;
    q.emplace(eval(puzzle), 0, puzzle);
    unordered_map<ll, ll> par;
    unordered_map<ll, char> pardir;
    par.reserve(int(1e6));
    pardir.reserve(int(1e6));
    par[hashstate(puzzle)] = hashstate(neutral);
    vector<char> dirc = { 'L','R', 'U','D' };
    while (sz(q))
    {
        int _, dis;
        state u;
        tie(_,dis,u) = q.top();
        q.pop();

        if (u == target)
        {
            break;
        }

        int specpos;
        rep(i, r * c) if (u[i] == r * c - 1) specpos = i;


        rep(d, 4)
        {
            p2 dir = dirs[d];
            p2 p = top2(specpos);
            p2 np = p2(p.first + dir.first, p.second + dir.second);
            if (np.first < 0 || np.second < 0 || np.first < r - 3 || np.second < c - 3 || np.first >= r || np.second >= c) continue;
            state ns = u;
            swap(ns[specpos], ns[toint(np)]);
            ll h = hashstate(ns);
            if (par.find(h) == par.end())
            {
                par[h] = hashstate(u);
                pardir[h] = dirc[d];
                q.emplace(eval(ns)+dis, dis+1, ns);
            }
        }
    }

    string extra;
    ll curr = hashstate(target);
    ll nhash = hashstate(neutral);
    while (curr != nhash)
    {
        if (pardir.find(curr) != pardir.end()) extra += pardir[curr];
        curr = par[curr];
    }
    reverse(all(extra));
    ans += extra;

    cout << ans << endl;

    return 0;
}
