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

struct Node
{
    Node* lchild;
    Node* rchild;
    int l, r;
    int sum;
    int lazy;

    Node(int l, int r) : lchild(nullptr), rchild(nullptr), l(l), r(r), sum(0), lazy(0) {}

    void push()
    {
        int mid = (l + r) / 2;
        if (!lchild)
        {
            lchild = new Node(l, mid);
            rchild = new Node(mid + 1, r);
        }
        lchild->sum = lchild->sum + lazy * (mid - l + 1);
        lchild->lazy = lchild->lazy + lazy;

        rchild->sum = rchild->sum + lazy * (r - (mid + 1) + 1);
        rchild->lazy = rchild->lazy + lazy;
        lazy = 0;
    }

    void add(int ql, int qr, int v)
    {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr)
        {
            sum = sum + v * (r - l + 1);
            lazy = lazy + v;
        }
        else
        {
            push();
            lchild->add(ql, qr, v);
            rchild->add(ql, qr, v);
            sum = rchild->sum + lchild->sum;
        }
    }

    int query(int ql, int qr)
    {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return sum;
        else
        {
            push();
            return lchild->query(ql, qr) + rchild->query(ql, qr);
        }
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<p2> mon(n);
    rep(i, n) cin >> mon[i].second;
    rep(i, n) cin >> mon[i].first;
    rep(i, n) mon[i].first = abs(mon[i].first);

    sort(all(mon));


    int lazy = 0;
    bool win = 1;
    int time = 0;
    rep(i, n)
    {
        if (mon[i].second <= lazy)
        {
            lazy -= mon[i].second;
        }
        else
        {
            mon[i].second -= lazy;
            lazy = 0;
            int v = ceildiv(mon[i].second, k);
            lazy = v * k;
            lazy -= mon[i].second;
            time += v;
            if (mon[i].first - time < 0) win = 0;
        }
    }

    cout << (win ? "YES" : "NO") << "\n";
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
