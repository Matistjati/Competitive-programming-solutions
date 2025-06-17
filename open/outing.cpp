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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct UF
{
    vi par;
    vi size;
    UF(int n) : par(n), size(n, 1)
    {
        rep(i, n)par[i] = i;
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

signed main()
{
    fast();


    int n, k;
    cin >> n >> k;
    vi who(n);
    rep(i, n) cin >> who[i];
    rep(i, n) who[i]--;

    UF uf(n);
    vi cyclehead;
    rep(i, n)
    {
        if (uf.find(i)!=uf.find(who[i]))
        {
            uf.merge(i, who[i]);
        }
        else
        {
            cyclehead.push_back(i);
        }
    }
    vi cyclesize;
    repe(c, cyclehead)
    {
        int s = 0;
        int u = c;
        do
        {
            u = who[u];
            s++;
        } while (u!=c);
        cyclesize.push_back(s);
    }

    bitset<1010> possible;
    possible[0] = 1;
    rep(i, sz(cyclehead))
    {
        bitset<1010> cop = possible;
        repp(j, cyclesize[i], uf.size[uf.find(cyclehead[i])] + 1)
        {
            possible |= cop << j;
        }
    }
    
    int ans = 0;
    rep(i, k + 1) if (possible[i]) ans = i;
    cout << ans;

    return 0;
}
