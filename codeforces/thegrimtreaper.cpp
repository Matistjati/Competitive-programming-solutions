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
    int cnt, prio;
    int value, sum;
    int max1, max2, maxc, lazy;
    node* l, * r;
    node(int value) : cnt(1), prio(dist(rng)), value(value), sum(value), max1(value), max2(-inf), maxc(1), lazy(0), l(nullptr), r(nullptr) {}
};

typedef node* pnode;
int get_cnt(pnode x) { return x ? x->cnt : 0; }
int get_sum(pnode x) { return x ? x->sum : 0; }

void push_max(pnode x, int h)
{
    if (!x) return;
    if (x->max1 <= h) return;
    x->sum -= x->max1 * x->maxc;
    x->max1 = h;
    x->sum += x->max1 * x->maxc;
    x->value = min(x->value, h);

}

void push_add(pnode x, int v)
{
    if (!x) return;
    x->sum += v * x->cnt;
    x->max1 += v;
    if (x->max2 != -inf) x->max2 += v;
    x->lazy += v;
    x->value += v;
}

void push(pnode x)
{
    if (!x) return;
    if (x->lazy)
    {
        push_add(x->l, x->lazy);
        push_add(x->r, x->lazy);
        x->lazy = 0;
    }
    push_max(x->l, x->max1);
    push_max(x->r, x->max1);
}

void merge_max(pnode x, pnode c)
{
    if (x->max1 == c->max1)
    {
        x->max1 = c->max1;
        x->maxc += c->maxc;
        x->max2 = max(x->max2, c->max2);
    }
    else if (x->max1 > c->max1)
    {
        x->max2 = max(x->max2, c->max1);
    }
    else
    {
        x->max2 = max(x->max1, c->max2);
        x->max1 = c->max1;
        x->maxc = c->maxc;
    }
    assert(x->max1 != x->max2);
}

void pull(pnode x)
{
    if (!x) return;
    x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1;
    x->sum = get_sum(x->l) + get_sum(x->r) + x->value;
    x->max1 = x->value;
    x->max2 = -inf;
    x->maxc = 1;
    if (x->l) merge_max(x, x->l);
    if (x->r) merge_max(x, x->r);
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
        split(x->r, x->r, r, i, add + 1 + get_cnt(x->l)), l = x;
    pull(x);
}

void merge(pnode& x, pnode l, pnode r)
{
    if (l) push(l);
    if (r) push(r);
    if (!l || !r)
        x = l ? l : r;
    else if (l->prio < r->prio)
        merge(r->l, l, r->l), x = r;
    else
        merge(l->r, l->r, r), x = l;
    pull(x);
}

void dfs_chmin(pnode x, int h)
{
    if (!x) return;
    if (h >= x->max1) return;
    if (h > x->max2)
    {
        push_max(x, h);
        return;
    }
    push(x);

    dfs_chmin(x->l, h);
    dfs_chmin(x->r, h);

    push_max(x, h);
    pull(x);
}

void chmin(pnode& x, int ql, int qr, int h)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);

    dfs_chmin(mid, h);

    merge(l, l, mid);
    merge(x, l, r);
}

int rsq(pnode& x, int ql, int qr)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);
    int ret = mid->sum;
    merge(l, l, mid);
    merge(x, l, r);
    return ret;
}

void print(pnode x)
{
    if (!x) return;
    print(x->l);
    cout << x->value << " ";
    print(x->r);
}


void add(pnode& x, int ql, int qr, int v)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);

    push_add(mid, v);

    merge(l, l, mid);
    merge(x, l, r);
}

void move_end(pnode& x, int ql, int qr)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);
    merge(l, l, r);
    merge(x, l, mid);
}

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    pnode root = nullptr;
    rep(i, n)
    {
        int v;
        cin >> v;
        pnode new_node = new node(v);
        merge(root, root, new_node);
    }

    while (q--)
    {
        int t, l, r;
        cin >> t >> l >> r;
        l--; r--;

        if (t == 1)
        {
            int h;
            cin >> h;
            chmin(root, l, r, h);
        }
        else if (t==2)
        {
            move_end(root, l, r);
        }
        else if (t==3)
        {
            int x;
            cin >> x;
            add(root, l, r, x);
        }
        cout << root->sum << "\n";
    }

    return 0;
}
