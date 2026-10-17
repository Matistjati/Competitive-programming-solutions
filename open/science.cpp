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

struct Edmonds
{
    vvi flow;
    vvi capacity;
    vi par;
    int n;
    int maxflow = 0;

    void addEdge(int a, int b, int c)
    {
        capacity[a][b] = c;
    }

    Edmonds(int n) : n(n), flow(n, vi(n)), capacity(n, vi(n)), par(n) {}

    int bfs(int s, int t)
    {
        rep(i, n) par[i] = -1;
        par[s] = -2;
        queue<p2> q;
        q.emplace(s, 1e9);

        while (q.size())
        {
            int u, f;
            tie(u, f) = q.front(); q.pop();

            rep(e, n)
            {
                if (par[e] == -1 && flow[u][e] < capacity[u][e])
                {
                    par[e] = u;
                    int newflow = min<int>(f, capacity[u][e] - flow[u][e]);

                    if (e == t) return newflow;
                    q.emplace(e, newflow);
                }
            }
        }

        return 0;
    }

    int augment(int s, int t) // find one augmenting path
    {
        int f = 0;
        if (f = bfs(s, t))
        {
            maxflow += f;
            for (int cur = t; cur != s; cur = par[cur])
            {
                int p = par[cur];
                flow[p][cur] += f;
                flow[cur][p] -= f;
            }

            return 1;
        }
        return 0;
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    const int source = n * 2;
    const int sink = n * 2+1;
    Edmonds flow(n*2+2);

    rep(i, n)
    {
        string row;
        cin >> row;
        rep(j, n)
        {
            if (row[j]=='Y')
            {
                flow.addEdge(i, j + n, 1);
            }
        }
    }

    vvi flowcopy;
    int ans = 0;
    rep(r, n)
    {
        rep(i, n) // add one capacity to source and sink
        {
            flow.capacity[source][i]++;
            flow.capacity[i+n][sink]++;
        }

        bool good = 1;
        rep(i, n) good &= flow.augment(source, sink);

        if (!good) break;
        ans++;
        flowcopy = flow.flow;
    }
    
    if (ans==0)
    {
        cout << "0";
        return 0;
    }

    int numnodes = n * 2 + 2;
    Edmonds flowans(n * 2 + 2);
    flowans.capacity = flowcopy;
    rep(i, numnodes) rep(j, numnodes) if (flowans.capacity[i][j] < 0) flowans.capacity[i][j] = 0;
    rep(i, n) // add one capacity to source and sink
    {
        flowans.capacity[source][i] = 1;
        flowans.capacity[i + n][sink] = 1;
    }

    cout << ans << "\n";
    rep(r, ans)
    {
        flowans.maxflow = 0;
        rep(i, numnodes) rep(j, numnodes) flowans.flow[i][j] = 0;
        while (flowans.augment(source, sink)) {}
        assert(flowans.maxflow == n);
        vi row(n, -1e9);
        rep(i, n)
        {
            rep(j, n)
            {
                if (flowans.flow[i][j+n])
                {
                    row[j] = i + 1;
                    flowans.flow[i][j + n] = 0;
                    flowans.flow[j+n][i] = 0;
                    flowans.capacity[i][j+n] = 0;
                    flowans.capacity[j+n][i] = 0;
                    break;
                }
            }
        }
        rep(i, n)
        {
            cout << row[i];
            cout << " ";
        }

        cout << "\n";
    }


    return 0;
}
