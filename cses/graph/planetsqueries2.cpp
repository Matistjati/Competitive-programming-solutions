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
int tin[maxn];
int tout[maxn];
int cp[maxn];
int timer = 0;

void dfs(int u, int d, int p, int par, vvi& redges)
{
    tin[u] = timer++;
    depth[u] = d;
    cyclepar[u] = p;
    cp[u] = par;
    repe(e, redges[u]) dfs(e, d + 1, p, par, redges);
    tout[u] = timer++;
}

bool isancestor(int a, int b)
{
    return tin[a] <= tin[b] && tin[b] <= tout[a];
}

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    vi next(n);
    vvi redges(n);
    rep(i, n) cin >> next[i], next[i]--;

    rep(i, n)
    {
        int b = next[i];
        redges[b].push_back(i);
    }

    vi incycle(n, -1);
    int cyclec = 0;
    vi cycleind(n);
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
            int ind = 0;
            while (incycle[u]==-1)
            {
                incycle[u] = cyclec;
                cycleind[u] = ind++;
                u = next[u];
            }
            cyclec++;
        }
    }
    vi cyclelen(cyclec);
    rep(i, n) if (incycle[i] != -1) cyclelen[incycle[i]]++;
    rep(i, n) if (incycle[i]==-1 && incycle[next[i]]!=-1) dfs(i, 1, incycle[next[i]], next[i], redges);


    while (q--)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        bool treea = incycle[a] == -1;
        bool treeb = incycle[b] == -1;
        if (treea&&treeb)
        {
            if (isancestor(b, a))
            {
                cout << depth[a] - depth[b] << "\n";
            }
            else cout << "-1\n";
        }
        else if (treea && !treeb)
        {
            if (cyclepar[a]!=incycle[b])
            {
                cout << "-1\n";
            }
            else
            {
                int pa = cycleind[cp[a]];
                int pb = cycleind[b];
                int d = pa <= pb ? pb - pa : pb + cyclelen[incycle[b]] - pa;
                cout << depth[a] + d << "\n";
            }
        }
        else if (treeb&&!treea)
        {
            cout << "-1\n";
        }
        else
        {
            if (incycle[a]!=incycle[b])
            {
                cout << "-1\n";
            }
            else
            {
                int pa = cycleind[a];
                int pb = cycleind[b];
                int d = pa <= pb ? pb - pa : pb + cyclelen[incycle[b]] - pa;
                cout << d << "\n";
            }
        }
    }

    return 0;
}
