// idea is basically: first, query {-inf,inf}. then, {-inf,inf}. these each produce k lines. their intersections give k^2 candidates
// to reduce this to one query, query both at once. we now have k^4 candidates
// generate random queries. ensure the possible distances produced by each one are disjoint
// for a given query, group points that would have the same distance. we start by finding points such that most groups become small
// then, add random queries
// then, use the info as best as possible: remove candidates in group whose distance is not present
// also keep track of groups of size 1: if we get k of these, we are done
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

int BIG = 1e8;
int b, k, w;
int dist(p2 a, p2 b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vi ask(vector<p2> coords)
{
    cout << "? ";
    repe(c, coords) cout << c.first << " " << c.second << " ";
    cout << endl;
    vi ret(sz(coords) * k);
    repe(v, ret) cin >> v;
    return ret;
}

signed main()
{
    fast();

    cin >> b >> k >> w;

    vi distances = ask({ {BIG,BIG},{-BIG,BIG} });

    set<p2> possibleintersections;
    repe(d1, distances)
    {
        repe(d2, distances)
        {
            int rhs = 4 * BIG - d1 - d2;
            if (rhs % 2 == 0)
            {
                int y = rhs / 2;
                int x = BIG * 2 - d1 - y;
                if (x<-BIG || x > BIG || y < -BIG || y > BIG) continue;
                possibleintersections.emplace(x, y);
            }
        }
    }

    vector<p2> isect(all(possibleintersections));

    unordered_set<int> seendists;
    seendists.reserve(int(5e6));
    vector<p2> query;
    mt19937 rng(20);
    uniform_int_distribution<int> distx(0, sz(isect) - 1);
    uniform_int_distribution<int> noise(-5, 5);
    uniform_int_distribution<int> distrand(-BIG, BIG);
    vi smallest(sz(isect), inf);
    // random coords: either completely random, or +- x or y coordinate of some candidate
    auto getvar = [&]()
        {
            int ret;
            if (distx(rng) % 2) ret = isect[distx(rng)].first + noise(rng);
            else if (distx(rng) % 2) ret = distrand(rng);
            else ret = isect[distx(rng)].second + noise(rng);
            if (distx(rng) % 2) ret *= -1;
            return ret;
        };

    // first, find queries that reduce group sizes
    rep(_, 5000)
    {
        if (sz(query) == 2000) break;
        p2 p = { getvar(),getvar() };

        if (p.first<-BIG || p.first>BIG || p.second<-BIG || p.second>BIG) continue;
        vi dists;

        bool good = 1;
        repe(c, isect)
        {
            if (seendists.contains(dist(p, c)))
            {
                good = 0;
                break;
            }
            dists.push_back(dist(p, c));
        }

        if (!good) continue;


        int decrease = 0;
        map<int, vi> group;
        rep(j, sz(isect)) group[dist(p, isect[j])].push_back(j);
        repe(g, group)
        {
            repe(u, g.second)
            {
                if (sz(g.second) < smallest[u]) decrease = 1;
            }
        }

        if (decrease == 0)
        {
            continue;
        }

        repe(g, group)
        {
            repe(u, g.second) smallest[u] = min(smallest[u], sz(g.second));
        }

        repe(d, dists) seendists.insert(d);
        query.push_back(p);
    }
    // fill up rest with random queries
    rep(_, 50000)
    {
        if (sz(query) == 2000) break;
        p2 p = { getvar(),getvar() };

        if (p.first<-BIG || p.first>BIG || p.second<-BIG || p.second>BIG) continue;
        vi dists;

        bool good = 1;
        repe(c, isect)
        {
            if (seendists.contains(dist(p, c)))
            {
                good = 0;
                break;
            }
            dists.push_back(dist(p, c));
        }

        if (!good) continue;

        repe(d, dists) seendists.insert(d);
        query.push_back(p);
    }

    vi res = ask(query);
    set<int> sres(all(res));
    while (true)
    {
        vi killed(sz(isect));
        vi provablyyes(sz(isect));
        repe(p, query)
        {
            vi dists;
            repe(c, isect) dists.push_back(dist(p, c));
            map<int, vi> distg;
            rep(i, sz(isect)) distg[dist(p, isect[i])].push_back(i);
            repe(g, distg)
            {
                if (!sres.count(g.first))
                {
                    repe(v, g.second) killed[v] = 1;
                }
                else if (sz(g.second) == 1)
                {
                    provablyyes[g.second[0]] = 1;
                }
            }
        }
        vector<p2> ans;
        if (accumulate(all(provablyyes), 0LL) == k)
        {
            rep(i, sz(isect)) if (provablyyes[i]) ans.push_back(isect[i]);
            isect = ans;
        }
        else
        {
            rep(i, sz(isect)) if (!killed[i]) ans.push_back(isect[i]);
        }
        if (sz(ans) == sz(isect)) break;
        isect = ans;
    }

    sort(all(isect));

    cout << "! ";
    repe(p, isect) cout << p.first << " " << p.second << " ";

    return 0;
}
