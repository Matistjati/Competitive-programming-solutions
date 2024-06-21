#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

bool dfs(int node, int color, std::vector<int>& colors, const std::vector<std::vector<int>>& adj) {
    colors[node] = color;

    for (int neighbor : adj[node]) {
        if (colors[neighbor] == -1) {
            // If neighbor hasn't been colored, color it with the opposite color
            if (!dfs(neighbor, 1 - color, colors, adj)) {
                return false;
            }
        }
        else if (colors[neighbor] == color) {
            // If neighbor has the same color, we found an odd cycle
            return false;
        }
    }
    return true;
}

bool containsOddCycle(const std::vector<std::vector<int>>& adj) {
    int n = adj.size();
    std::vector<int> colors(n, -1);

    for (int i = 0; i < n; ++i) {
        if (colors[i] == -1) {
            if (!dfs(i, 0, colors, adj)) {
                return true;
            }
        }
    }
    return false;
}

signed main()
{
    fast();
    int n, m;
    cin >> n >> m;


    vvi adj(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    if (containsOddCycle(adj)) cout << "no way";
    else cout << "attend here" << std::endl;
    
    return 0;
}
