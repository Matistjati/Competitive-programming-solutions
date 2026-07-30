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

using vb = vector<bool>;
using vvb = vector<vb>;
bool bpm(vvb& graph, ll u, vb& seen, vi& matchR)
{
    for (ll v = 0; v < graph.size(); v++)
    {
        if (graph[u][v] && !seen[v])
        {
            seen[v] = true;

            if (matchR[v] < 0 || bpm(graph, matchR[v],
                seen, matchR))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

ll maxBPM(vvb& graph)
{
    vi matchR(graph.size(),-1);

    ll matches = 0;
    for (ll u = 0; u < graph.size(); u++)
    {
        vb seen(graph.size());

        if (bpm(graph, u, seen, matchR))
            matches++;
    }
    return matches;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n, k, m;
    cin >> n >> k >> m;

    vector<string> cubes(n);
    for (auto& v : cubes) cin >> v;
    vector<string> words(m);
    for (auto& v : words) cin >> v;

    vvb graph(n, vb(n));
    ll ans = 0;

    repe(word, words)
    {
        repe(g, graph) {
            fill(all(g), 0);
        }

        map<char, vector<ll>> wordMap;
        ll i = 0;
        repe(c, word)
        {
            wordMap[c].emplace_back(i);
            i++;
        }

        rep(i, cubes.size())
        {
            string cube = cubes[i];
            repe(c, cube)
            {
                repe(index, wordMap[c])
                {
                    graph[i][index] = true;
                }
            }
        }

        ll matches = maxBPM(graph);

        if (matches>=n)
        {
            ans++;
        }
    }

    cout << ans;

    return 0;
}
