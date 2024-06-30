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
#define __builtin_clz _lzcnt_u32
#define assert(x) if (!(x)) __debugbreak()
#endif

int ask(const vi guess)
{
    set<int> unique(all(guess));
    cout << "? " << sz(unique);
    for (int x : unique) {
        cout << " " << x + 1;
    }
    cout << endl << flush;
    string answer;
    cin >> answer;
    return (answer == "YES");
}

vi merge(vi a, vi b)
{
    repe(u, b)a.push_back(u);
    return a;
}

signed main()
{
    fast();

    int n;
    cin >> n;
    
    vvi edges(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    vi leafs;
    vi nonleafs;
    rep(i, n)
    {
        if (sz(edges[i]) == 1) leafs.push_back(i);
        else nonleafs.push_back(i);
    }
    vi order(leafs);
    repe(u, nonleafs) order.push_back(u);
    
    int lo = 0;
    int hi = n;
    while (lo+2<hi)
    {
        int mid = (lo + hi) / 2;
        vi slice;
        rep(i, mid) slice.push_back(order[i]);
        if (sz(slice) == 1) slice.push_back(order[mid]);
        if (ask(slice))
        {
            hi = mid;
        }
        else lo = mid;
    }

    int mid = (lo + hi) / 2;
    vi slice = { order[lo] };
    if (lo + 1 < sz(order)) slice.push_back(order[lo + 1]);
    if (sz(slice)==1)
    {
        cout << "! " << slice[0] + 1;
    }
    else
    {
        if (find(all(leafs),slice[1])!=leafs.end())
        {
            leafs.erase(find(all(leafs), slice[1]));
        }
        if (ask(merge({ slice[0]}, leafs)))
        {
            cout << "! " << slice[0] + 1;
        }
        else
        {
            cout << "! " << slice[1] + 1;
        }
    }

    return 0;
}
