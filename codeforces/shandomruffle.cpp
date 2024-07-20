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
uniform_int_distribution<int> dist(1, int(1e9));
struct node
{
    int cnt, prio, value;
    node *l, *r;
    node(int value) : cnt(1), prio(dist(rng)), value(value), l(nullptr),r(nullptr) {}
};

typedef node* pnode;
int get_cnt(pnode x) { return x ? x->cnt : 0; }

void pull(pnode x)
{
    if (x)
    {
        x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1;
    }
}

void push(pnode x)
{
    
}

void split(pnode x, pnode& l, pnode& r, int i, int add = 0)
{
    if (!x)
        return void(l = r = nullptr);
    push(x);
    int real_i = get_cnt(x->l) + add;
    if (i <= real_i)
        split(x->l, l, x->l, i, add), r = x;
    else
        split(x->r, x->r, r, i, add + get_cnt(x->l) + 1), l = x;
    pull(x);
}

void merge(pnode& x, pnode l, pnode r)
{
    push(l);
    push(r);
    if (!l || !r)
        x = l ? l : r;
    else if (l->prio < r->prio)
        merge(r->l, l, r->l), x = r;
    else
        merge(l->r, l->r, r), x = l;
    pull(x);
}

void insert(pnode& x, int p, int v)
{
    pnode l, r;
    split(x, l, r, p);
    pnode new_node = new node(v);
    merge(l, l, new_node);
    merge(x, l, r);
}

void print(pnode x)
{
    if (!x) return;
    print(x->l);
    cout << x->value << " ";
    print(x->r);
}

void shandom(pnode& x, int ql, int qr, int len)
{
    pnode l, m1, m2, m3, r;
    split(x, m3, r, qr + len);
    split(m3, m2, m3, qr);
    split(m2, m1, m2, ql+len);
    split(m1, l, m1, ql);

    merge(l, l, m3);
    merge(l, l, m2);
    merge(l, l, m1);
    merge(x, l, r);
}

signed main()
{
    fast();

    int n;
    cin >> n;

    pnode root = nullptr;
    rep(i, n) insert(root, 0, n-i);


    rep(i, n)
    {
        int l, r;
        cin >> l >> r;
        if (l >= r) continue;
        l--; r--;
        int len = min(n - r, r - l);
        shandom(root, l, r, len);
    }
    print(root);

    return 0;
}
