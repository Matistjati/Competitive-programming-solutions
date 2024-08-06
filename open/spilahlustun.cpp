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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

mt19937 rng;
uniform_int_distribution<int> dist(0, 1e9);
struct node
{
    int cnt, prio, val;
    bool rev, flip, lflip;
    node* l = 0, * r = 0;
    node(int value) : cnt(1), prio(dist(rng)), val(value), rev(0), flip(0) {}
};

typedef node* pnode;
int get_cnt(pnode x) { return x ? x->cnt : 0; }
void pull(pnode x) { if (x) x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1; }

void apply_flip(pnode x)
{
    if (!x) return;
    x->flip ^= 1;
    x->lflip ^= 1;
}

void push(pnode x)
{
    if (!x) return;
    if (x->rev)
    {
        swap(x->l, x->r);
        if (x->l) x->l->rev ^= 1;
        if (x->r) x->r->rev ^= 1;
        x->rev = 0;
    }
    if (x->lflip)
    {
        apply_flip(x->l);
        apply_flip(x->r);
        x->lflip = 0;
    }
}

void split(pnode x, pnode& l, pnode& r, int i, int add = 0)
{
    if (!x) return void(l = r = 0);
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

void revinterval(pnode& x, int ql, int qr)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);
    apply_flip(mid);
    mid->rev ^= 1;
    merge(l, l, mid);
    merge(x, l, r);
}

void print(pnode x)
{
    if (!x) return;
    push(x);
    print(x->l);
    cout << (x->flip ? "-" : "") << x->val << " ";
    print(x->r);
}

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    pnode root = 0;
    rep(i, n)
    {
        merge(root, root, new node(i + 1));
    }

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--; r--;
        revinterval(root, l, r);
    }
    print(root);

    return 0;
}
