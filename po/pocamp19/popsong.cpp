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

const ll maxN = (ll)(2e5 + 1);

void fail() {
    cout << 0 << "\n";
    exit(0);
}

using vvp2 = vector<vector<p2>>;
ll getfurthestnode(vvp2& edges, bitset<maxN>& mustVisit, ll n, ll start)
{
    ll costiest = inf;
    ll deepestNode = -1;
    ll parent = start;

    priority_queue<p2> pq;
    pq.emplace(0, start);
    vi seen(n);

    while (pq.size())
    {
        ll cost, node;
        tie(cost, node) = pq.top();
        pq.pop();

        if (seen[node]) continue;
        seen[node] = true;

        bool heavyNode = mustVisit.test(node);
        if (heavyNode)
        {
            if (cost < costiest)
            {
                costiest = cost;
                deepestNode = node;
            }
        }

        repe(adj, edges[node])
        {
            pq.emplace(cost+adj.first, adj.second);
        }
    }

    return deepestNode;
}

void findVaild(vvp2& edges, set<ll>& ans, bitset<maxN>& mustVisit, ll n, ll start) {
    priority_queue<tuple<int,int,int>> pq;
    pq.emplace(0, -(ll)mustVisit.count(), start);
    vi seen(n);

    while (pq.size())
    {
        ll cost, n_left, node;
        tie(cost, n_left, node) = pq.top();
        pq.pop();

        if (seen[node]) continue;
        seen[node] = true;

        if (mustVisit.test(node))
        {
            n_left++;
        }

        if (n_left==0) ans.insert(node);

        repe(adj, edges[node])
        {
            pq.emplace(cost + adj.first, n_left, adj.second);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m, k;
    cin >> n >> m >> k;

    vvp2 edges(n);

    vi mustVisit(k);
    bitset<maxN> seenAxel;
    rep(i, k)
    {
        ll v;
        cin >> v;
        v--;
        seenAxel.set(v);
        mustVisit[i] = v;
    }

    rep(i,m)
    {
        ll a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        edges[a].emplace_back(-w, b);
        edges[b].emplace_back(-w, a);
    }

    ll deepestLeft = getfurthestnode(edges, seenAxel, n, mustVisit[0]);
    ll deepestRight = getfurthestnode(edges, seenAxel, n, deepestLeft);

    set<ll> ans;

    findVaild(edges, ans, seenAxel, n, deepestLeft);
    findVaild(edges, ans, seenAxel, n, deepestRight);

    cout << sz(ans) << "\n";

    repe(y,ans) {
        cout << y + 1 << " ";
    }

    return 0;
}
