#include <bits/stdc++.h>
using namespace std;


typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int k = 30;
const int n = 1000;
bitset<n*n> edges;
std::vector<std::pair<int,int>> run(std::vector<std::pair<int,int>> S)
{
    int m = S.size();
    vector<p2> graph;
    vi deg(n);
    rep(i, m)
    {
        int a,b;
        tie(a,b)=S[i];
        edges[a*n+b]=1;
        edges[b*n+a]=1;
        deg[a]++;
        deg[b]++;
        graph.emplace_back(a,b);
    }
    vector<p2> nodes;
    rep(i, n) nodes.emplace_back(deg[i], i);
    sort(nodes.rbegin(), nodes.rend());

    if (nodes[0].first!=nodes[1].first)
    {
        int cnt = 0;
        int rounds = 1;
        while (rounds<k)
        {
            int s = rounds;
            while (nodes[s].second==nodes[rounds].second)
            {
                cnt += edges[nodes[0].second * n + nodes[s].second];
                s++;
            }
            rounds = s;
        }
        if (cnt>20)
        {
            // NOT first
            return {};
        }
    }

    int root = nodes[0].second;
    int placed = 0;
    int i = 1;
    vector<p2> ret;
    while (placed < k)
    {
        if (!edges[root*n+nodes[i].second])
        {
            ret.emplace_back(root, nodes[i].second);
            placed++;
        }
        i++;
    }
    return ret;
}
