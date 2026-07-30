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

using vp2 = vector<p2>;
using p3 = tuple<ll,ll,ll>;

struct UF {
    vi e;
    UF(ll n) : e(n, -1) {}
    bool sameSet(ll a, ll b) { return find(a) == find(b); }
    ll size(ll x) { return -e[find(x)]; }
    ll find(ll x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(ll a, ll b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};



int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n, k;
    cin >> n >> k;

    map<ll, vi> cols;
    map<p2, ll> posToIndex;

    vp2 positions(n);

    rep(i, n)
    {
        ll x, y;
        cin >> x >> y;

        positions[i] = { x,y + 1 };
        if (!cols.count(x))
        {
            cols[x] = {};
        }
        cols[x].emplace_back(y);
        posToIndex[make_pair(x, y)] = i;
    }

    repe(col, cols)
    {
        sort(all(col.second));
    }

    queue<ll> q;
    q.push(0);
    vi visited(n);

    vi offsets = { 1,-1 };

    priority_queue<p3> events;

    while (q.size())
    {
        ll curr = q.front();
        q.pop();

        if (visited[curr])
        {
            continue;
        }
        visited[curr] = true;

        p2 p = positions[curr];

        auto above = upper_bound(all(cols[p.first]), p.second);
        ll aboveHeight = above != cols[p.first].end() ? *above : inf;

        repe(offset, offsets)
        {
            if (cols.count(p.first + offset))
            {
                vi& col = cols[p.first + offset];
                if (col.empty())
                {
                    continue;
                }

                auto start = upper_bound(all(col), p.second);
                auto ending = lower_bound(all(col), aboveHeight - 1);

                if (start != col.begin())
                {
                    start = prev(start);
                }

                for (; start < ending; start = next(start))
                {
                    ll index = posToIndex[make_pair(p.first + offset, *start)];
                    ll t = abs(p.second-1-*start);
                    events.push({ -t, index, curr });
                    q.emplace(index);
                }
            }
        }

    }

    UF uf(n);
    if (n==1)
    {
        cout << 0;
        return 0;
    }
    else
    {
        while (events.size())
        {
            ll t, a, b;
            tie(t, a, b) = events.top();
            events.pop();

            uf.join(a, b);

            if (uf.sameSet(0, n - 1))
            {
                t = (-t);
                cout << ((t < k) ? to_string(t) : "NATT");
                return 0;
            }
        }
    }

    cout << "NATT";

    return 0;
}
