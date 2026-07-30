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


p2 shortest(map<int, set<p2>>& edges, int start, int n)
{
    vector<int> d(n+1, 1e9);
    d[start] = 0;

    priority_queue<p2> pq;
    pq.push({ 0,start });

    set<int> visited;

    while (pq.size())
    {
        p2 curr = pq.top();
        pq.pop();

        visited.insert(curr.second);

        repe(edge, edges[curr.second])
        {
            if (!visited.count(edge.second))
            {
                int old_cost = d[edge.second];
                int new_cost = edge.first + d[curr.second];
                if (new_cost < old_cost)
                {
                    pq.push({ -new_cost ,edge.second });
                    d[edge.second] = new_cost;
                }
            }
        }

    }

    d[0] = -1;
    auto it = max_element(d.begin(), d.end());
    return {it-d.begin(),*it};
}

int main() {
    cin.tie()->sync_with_stdio(0);

    int n,v;
    cin >> n >> v;

    map<int, set<p2>> edges;
    rep(i, v) {
        int houseA, houseB, length;
        cin >> houseA >> houseB >> length;

        if (!edges.count(houseA))
        {
            edges[houseA] = set<p2>();
        }
        if (!edges.count(houseB))
        {
            edges[houseB] = set<p2>();
        }
        edges[houseA].insert({ length, houseB });
        edges[houseB].insert({ length, houseA });
    }

    int longest = -1;
    int a = -1;
    int b = -1;

    for (int i = 1; i < n + 1; i++)
    {
        p2 dist = shortest(edges, i, n);
        if (dist.second > longest)
        {
            a = i;
            b = dist.first;
            longest = dist.second;
        }
    }
    cout << a << ' ' << b << ' ' << longest*100 << endl;

    return 0;
}
