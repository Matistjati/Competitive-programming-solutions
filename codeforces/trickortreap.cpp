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

mt19937 rng;
uniform_int_distribution<int> dist(1, int(1e18));
struct node
{
    int sum, value, cnt, prio;
    node* l, * r, * par;
    node(int value) : sum(value), value(value), cnt(1), prio(dist(rng)), l(nullptr), r(nullptr), par(nullptr) {}
};

typedef node* pnode;

int get_cnt(pnode x) { return x ? x->cnt : 0; }
int get_sum(pnode x) { return x ? x->sum : 0; }

void pull(pnode x)
{
    if (!x) return;
    x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1;
    x->sum = get_sum(x->l) + get_sum(x->r) + x->value;
    if (x->l) x->l->par = x;
    if (x->r) x->r->par = x;
}

void split(pnode x, pnode& l, pnode& r, int i, int add = 0)
{
    if (!x)
        return void(l = r = nullptr);
    int real_i = get_cnt(x->l) + add;
    if (i <= real_i)
        split(x->l, l, x->l, i, add), r = x;
    else
        split(x->r, x->r, r, i, add + get_cnt(x->l) + 1), l = x;
    pull(x);
}

void merge(pnode& x, pnode l, pnode r)
{
    if (!l || !r)
        x = l ? l : r;
    else if (l->prio < r->prio)
        merge(r->l, l, r->l), x = r;
    else
        merge(l->r, l->r, r), x = l;
    pull(x);
}

pnode get_root(pnode x)
{
    while (x->par != nullptr) x = x->par;
    return x;
}

signed main()
{
    fast();

    int q;
    cin >> q;
    map<int, pnode> nodes;

    rep(i, q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int v;
            cin >> v;
            pnode p = new node(v);
            nodes[i + 1] = p;
        }
        else if (t == 2)
        {
            int y, z;
            cin >> y >> z;
            pnode a = nodes[y];
            a = get_root(a);
            pnode b = nodes[z];
            b = get_root(b);
            if (a->prio == b->prio) continue;

            merge(a, a, b);
        }
        else if (t == 3)
        {
            int y, z;
            cin >> y >> z;
            pnode a = nodes[y];
            a = get_root(a);
            if (get_cnt(a) <= z) continue;
            pnode l, r;
            split(a, l, r, z);
            l->par = nullptr;
            r->par = nullptr;
        }
        else
        {
            int y;
            cin >> y;
            pnode a = nodes[y];
            a = get_root(a);
            cout << get_sum(a) << "\n";
        }
    }

    return 0;
}
