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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

constexpr int maxn = int(2e5);
int depth[maxn];
int cyclepar[maxn];

void dfs(int u, int d, int p, vvi& redges)
{
    depth[u] = d;
    cyclepar[u] = p;
    repe(e, redges[u]) dfs(e, d + 1, p, redges);
}

signed main()
{
    fast();

    int n;
    cin >> n;
    vi next(n);
    vvi redges(n);
    rep(i, n) cin >> next[i], next[i]--;

    rep(i, n)
    {
        int a = i;
        int b = next[i];
        redges[b].push_back(i);
    }

    vi incycle(n, -1);
    int cyclec = 0;

    vi seen(n);
    rep(i, n)
    {
        int u = i;
        set<int> vis;
        bool head = 0;
        while (incycle[u]==-1)
        {
            if (vis.find(u)!=vis.end())
            {
                head = 1;
                break;
            }
            if (seen[u]) break;
            seen[u] = 1;
            vis.insert(u);
            u = next[u];
        }
        if (head)
        {
            while (incycle[u]==-1)
            {
                incycle[u] = cyclec;
                u = next[u];
            }
            cyclec++;
        }
    }
    vi cyclelen(cyclec);
    rep(i, n) if (incycle[i] != -1) cyclelen[incycle[i]]++;
    rep(i, n) if (incycle[i]==-1 && incycle[next[i]]!=-1) dfs(i, 1, incycle[next[i]], redges);


    rep(i, n)
    {
        if (incycle[i]!=-1) cout << cyclelen[incycle[i]] << " ";
        else cout << cyclelen[cyclepar[i]]+depth[i] << " ";
    }

    return 0;
}
