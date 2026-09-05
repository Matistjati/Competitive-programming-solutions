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


p2 shortest(vector<vector<p2>>& adj, int start) {
    vector<int> dist(sz(adj), 1e9);
    dist[start] = 0;

    priority_queue<p2> pq;
    pq.push({ 0,start });

    while (sz(pq)) {
        auto [d,u] = pq.top();
        pq.pop();

        d=-d;
        if (d>dist[u]) continue;

        for (auto [e, w] : adj[u]) {
            if (w+d < dist[e]) {
                dist[e] = w+d;
                pq.push({-(w+d), e});
            }
        }
    }

    auto it = max_element(all(dist));
    return {it-begin(dist), *it};
}

int main() {
    cin.tie()->sync_with_stdio(0);

    int n,m;
    cin >> n >> m;

    vector<vector<p2>> adj(n);
    rep(i, m) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;

        adj[a].emplace_back(b,w);
        adj[b].emplace_back(a,w);
    }

    int longest = -1;
    int a = -1;
    int b = -1;

    rep(i, n) {
        p2 dist = shortest(adj, i);
        if (dist.second > longest) {
            a = i;
            b = dist.first;
            longest = dist.second;
        }
    }
    cout << a+1 << ' ' << b+1 << ' ' << longest*100 << endl;

    return 0;
}
