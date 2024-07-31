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
uniform_int_distribution<int> dist(0, 1e9);
struct node
{
    int cnt, prio, value;
    bool rev=0;
    node* l=0, * r = 0;
    node(int value ) : cnt(1), prio(dist(rng)), value(value) {}
};

typedef node* pnode;
int get_cnt(pnode x) { return x ? x->cnt : 0; }

void pull(pnode x)
{
    if (!x) return;
    x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1;
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
}

void split(pnode x, pnode& l, pnode& r, int i, int add = 0)
{
    if (!x)
        return void(l = r = 0);
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

void rev(pnode& x, int ql, int qr)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);
    mid->rev ^= 1;
    merge(l, l, mid);
    merge(x, l, r);
}

void get(pnode x, int i, int add = 0)
{
    push(x);
    int real_ind = get_cnt(x->l) + add;
    if (i == real_ind)
    {
        cout << x->value << " ";
        return;
    }
    if (i < real_ind) get(x->l, i, add);
    else get(x->r, i, add + get_cnt(x->l) + 1);
}

signed main()
{
    fast();
	
    node* a;
    int n, q, m;
    cin >> n >> q >> m;
    pnode root = nullptr;
    rep(i, n)
    {
        int v;
        cin >> v;
        pnode u = new node(v);
        merge(root, root, u);
    }

    while (q--)
    {
        int t, ql, qr;
        cin >> t >> ql >> qr;
        ql--; qr--;

        if (t==1)
        {
            pnode l, mid, r;
            split(root, l, r, qr + 1);
            split(l, l, mid, ql);
            pnode m1;
            split(mid, mid, m1, mid->cnt-1);
            merge(mid, m1, mid);
            merge(l, l, mid);
            merge(root, l, r);
        }
        else
        {
            rev(root, ql, qr);
        }
    }

    rep(i, m)
    {
        int k;
        cin >> k;
        k--;
        get(root, k);
    }

    return 0;
}
