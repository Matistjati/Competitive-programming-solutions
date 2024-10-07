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
const int maxd = 10;

int prefsum[maxd + 1][int(2e5)];
struct UF
{
    int numcomps;
    vi par;
    vi size;
    UF(int n) : par(n), size(n, 1), numcomps(n)
    {
        rep(i, n) par[i] = i;
    }
    int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        numcomps--;
        par[b] = a;
        size[a] += size[b];
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    rep(i, maxd + 1) rep(k, n) prefsum[i][k] = 0;
    rep(i, m)
    {
        int a, d, k;
        cin >> a >> d >> k;
        a--;
        if(a+d<n) prefsum[d][a+d] += 1;
        if(a+d*(k+1)<n) prefsum[d][a+d*(k+1)] -= 1;
    }
    UF uf(n);
    repp(d, 1, maxd + 1)
    {
        rep(i, n)
        {
            if (i - d >= 0)
            {
                prefsum[d][i] += prefsum[d][i - d];
                if (prefsum[d][i]>0)
                {
                    uf.merge(i, i - d);
                }
            }
        }
    }
    cout << uf.numcomps << "\n";
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
