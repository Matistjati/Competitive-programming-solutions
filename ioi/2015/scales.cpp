#include "scales.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll linf = ll(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int q1(const vi& items, int a, int b, int c)
{
    if (items[a] > items[b] && items[a] > items[c]) return a;
    if (items[b] > items[a] && items[b] > items[c]) return b;
    if (items[c] > items[b] && items[c] > items[a]) return c;
}
int q2(const vi& items, int a, int b, int c)
{
    if (items[a] < items[b] && items[a] < items[c]) return a;
    if (items[b] < items[a] && items[b] < items[c]) return b;
    if (items[c] < items[b] && items[c] < items[a]) return c;
}
int q3(const vi& items, int a, int b, int c)
{
    vector<p2> v;
    v.emplace_back(items[a], a);
    v.emplace_back(items[b], b);
    v.emplace_back(items[c], c);
    sort(all(v));
    return v[1].second;
}
int q4(const vi& items, int a, int b, int c, int d)
{
    vector<p2> heavier;
    if (items[a] > items[d]) heavier.emplace_back(items[a], a);
    if (items[b] > items[d]) heavier.emplace_back(items[b], b);
    if (items[c] > items[d]) heavier.emplace_back(items[c], c);
    if (sz(heavier))
    {
        sort(all(heavier));
        return heavier[0].second;
    }
    else
    {
        return q2(items, a, b, c);
    }
}

vvi all_perm;
uniform_int_distribution<int> adist(0, 3);
uniform_int_distribution<int> ndist(0, 5);
mt19937 rng(rand());
vi getmove()
{
    int move = adist(rng);
    if (move == 0)
    {
        int a, b, c;
        a = ndist(rng);
        b = ndist(rng);
        while (b == a) b = ndist(rng);
        c = ndist(rng);
        while (c == b || c == a) c = ndist(rng);

        return {0,a,b,c};
    }
    if (move == 1)
    {
        int a, b, c;
        a = ndist(rng);
        b = ndist(rng);
        while (b == a) b = ndist(rng);
        c = ndist(rng);
        while (c == b || c == a) c = ndist(rng);
        
        return {1,a,b,c};
    }
    if (move == 2)
    {
        int a, b, c;
        a = ndist(rng);
        b = ndist(rng);
        while (b == a) b = ndist(rng);
        c = ndist(rng);
        while (c == b || c == a) c = ndist(rng);

        return {2,a,b,c};
    }
    else
    {
        int a, b, c, d;
        a = ndist(rng);
        b = ndist(rng);
        while (b == a) b = ndist(rng);
        c = ndist(rng);
        while (c == b || c == a) c = ndist(rng);
        d = ndist(rng);
        while (d == a || d == b || d == c) d = ndist(rng);

        return {3,a,b,c, d};
    }
}

vi filter(const vi& possible, vi& query)
{
    vi ret;

    if (query[0] == 0)
    {
        int resp = getHeaviest(query[1] + 1, query[2] + 1, query[3] + 1) - 1;
        repe(p, possible)
        {
            if (q1(all_perm[p], query[1], query[2], query[3]) == resp)
            {
                ret.push_back(p);
            }
        }
    }
    else if (query[0] == 1)
    {
        int resp = getLightest(query[1] + 1, query[2] + 1, query[3] + 1) - 1;
        repe(p, possible)
        {
            if (q2(all_perm[p], query[1], query[2], query[3]) == resp)
            {
                ret.push_back(p);
            }
        }
    }
    else if (query[0] == 2)
    {
        int resp = getMedian(query[1] + 1, query[2] + 1, query[3] + 1) - 1;
        repe(p, possible)
        {
            if (q3(all_perm[p], query[1], query[2], query[3]) == resp)
            {
                ret.push_back(p);
            }
        }
    }
    else if (query[0] == 3)
    {
        int resp = getNextLightest(query[1] + 1, query[2] + 1, query[3] + 1, query[4] + 1) - 1;
        repe(p, possible)
        {
            if (q4(all_perm[p], query[1], query[2], query[3], query[4]) == resp)
            {
                ret.push_back(p);
            }
        }
    }
    else assert(0);
    return ret;
}

vvi fakefilter(const vi& possible, const vi& q)
{
    vvi res(6);
    repe(g, possible)
    {
        int v;
        if (q[0] == 0) v = q1(all_perm[g], q[1], q[2], q[3]);
        if (q[0] == 1) v = q2(all_perm[g], q[1], q[2], q[3]);
        if (q[0] == 2) v = q3(all_perm[g], q[1], q[2], q[3]);
        if (q[0] == 3) v = q4(all_perm[g], q[1], q[2], q[3], q[4]);
        res[v].push_back(g);        
    }
    
    return res;
}


vi allowed = { 243, 81, 27, 9, 3, 1 };
map<vi, vi> questions;
int rec(const vi& possible, int depth)
{
    if (sz(possible)==1)
    {
        return 0;
    }
    
    vvi queries;
    rep(a, 6) repp(b, a+1, 6) repp(c, b+1, 6) rep(d, 6)
    {
        if (a == d || b == d || c == d) continue;
        queries.emplace_back(vi({ 3, a, b, c, d }));
    }
        
    rep(q, 3)
    {
        if (q == 3) continue;
        rep(a, 6) repp(b, a+1, 6) repp(c, b+1, 6)
        {
            if (a == b || b == c || c == a) continue;
            queries.emplace_back(vi({ q, a, b, c }));
        }
    }
    shuffle(all(queries), rng);


    int ret = 1000000;
    repe(q, queries)
    {
        int cost = 0;
        vvi res = fakefilter(possible, q);
        repe(u, res)
        {
            if (sz(u) > allowed[depth])
            {
                cost = 100000;
                break;
            }
        }
        if (cost!= 100000)
        {
            repe(u, res)
            {
                if (sz(u)) cost = max(cost, 1 + rec(u, depth + 1));
            }
        }
        ret = min(ret, cost);
        if (depth+ret<=6)
        {
            questions[possible] = q;
            break;
        }
    }
    return ret;
}

void init(int T) {
    vi order = { 1,2,3,4,5,6 };
    do
    {
        all_perm.push_back(order);
    } while (next_permutation(order.begin(),order.end()));
    vi possible;
    rep(i, 720) possible.push_back(i);
    cerr << rec(possible, 0);
    return;
}

void orderCoins() {

    vi possible(720);
    rep(i, 720) possible[i] = i;
    
    while (sz(possible)>1)
    {
        possible = filter(possible, questions[possible]);
    }


    vi p = all_perm[possible[0]];
    int W[] = { 0,
                0, 
                0, 
                0, 
                0, 
                0};
    rep(i, 6) W[p[i]-1] = i + 1;
    answer(W);
}
