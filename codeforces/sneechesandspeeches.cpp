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
    int lp, rp, mp;
    int flp, frp, fmp;
    int zerocnt, onecnt, push_set;
    bool rev, lazy, value;
    node* l, * r;

    int& glp(bool flip) { return flip ? flp : lp; }
    int& grp(bool flip) { return flip ? frp : rp; }
    int& gmp(bool flip) { return flip ? fmp : mp; }

    void apply(bool f) // lp = left prefix of zeros
    {
        if (l && r)
        {
            if (value != f)
            {
                glp(f) = l->glp(f);
                grp(f) = r->grp(f);
                gmp(f) = max(l->gmp(f), r->gmp(f));
            }
            else
            {
                gmp(f) = max(r->gmp(f), l->gmp(f));
                gmp(f) = max(gmp(f), 1 + l->grp(f) + r->glp(f));
                grp(f) = r->grp(f);
                glp(f) = l->glp(f);

                if (l->cnt == l->glp(f)) glp(f) = l->glp(f) + 1 + r->glp(f);
                if (r->cnt == r->grp(f)) grp(f) = r->grp(f) + 1 + l->grp(f);
            }
        }
        else if (l || r)
        {
            node* c = l ? l : r;
            int v = value;
            gmp(f) = c->gmp(f);
            if (v != f)
            {
                grp(f) = glp(f) = 0;
                if (l) glp(f) = l->glp(f);
                if (r) grp(f) = r->grp(f);
            }
            else
            {
                if (l) gmp(f) = max(gmp(f), 1 + l->grp(f));
                else gmp(f) = max(gmp(f), 1 + r->glp(f));

                if (l)
                {
                    grp(f) = 1 + l->grp(f);
                    glp(f) = l->glp(f) + (l->cnt == l->glp(f));
                }
                else
                {
                    glp(f) = 1 + r->glp(f);
                    grp(f) = r->grp(f) + (r->cnt == r->grp(f));
                }
            }
        }
        else
        {
            glp(f) = grp(f) = gmp(f) = value == f;
        }
    }

    void flip()
    {
        if (push_set != -1) // pending update
        {
            push_set = push_set == 1 ? 0 : 1;
            push_set_range(push_set);
            return;
        }
        swap(lp, flp);
        swap(rp, frp);
        swap(mp, fmp);
        swap(zerocnt, onecnt);
        value ^= 1;
        lazy ^= 1;
    }

    void reverse()
    {
        rev ^= 1;
        swap(l, r);
        swap(lp, rp);
        swap(flp, frp);
    }

    void push_set_range(int v)
    {
        assert(v != -1);
        if (v == 1)
        {
            lp = rp = mp = zerocnt = 0;
            flp = frp = fmp = onecnt = cnt;
            value = 1;
            lazy = 0;
            push_set = 1;
        }
        else
        {
            lp = rp = mp = zerocnt = cnt;
            flp = frp = fmp = onecnt = 0;
            value = 0;
            lazy = 0;
            push_set = 0;
        }
    }

    node() : lp(0), rp(0), mp(0), flp(0), frp(0), fmp(0), zerocnt(1), onecnt(0), push_set(-1),
        cnt(1), prio(dist(rng)), value(0), lazy(0), rev(0), l(nullptr), r(nullptr)
    {
        apply(0);
        apply(1);
    }
};

typedef node* pnode;

int get_cnt(pnode x) { return x ? x->cnt : 0; }
int get_zerocnt(pnode x) { return x ? x->zerocnt : 0; }
int get_onecnt(pnode x) { return x ? x->onecnt : 0; }

void push(pnode x)
{
    if (!x) return;
    if (x->rev)
    {
        x->rev = 0;
        if (x->l) x->l->reverse();
        if (x->r) x->r->reverse();
    }
    if (x->push_set != -1)
    {
        if (x->l) x->l->push_set_range(x->push_set);
        if (x->r) x->r->push_set_range(x->push_set);
        x->push_set = -1;
    }
    if (x->lazy)
    {
        if (x->l) x->l->flip();
        if (x->r) x->r->flip();
        x->lazy = 0;
    }
}

void pull(pnode x)
{
    if (!x) return;
    x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1;
    x->zerocnt = get_zerocnt(x->l) + get_zerocnt(x->r) + (x->value == 0);
    x->onecnt = get_onecnt(x->l) + get_onecnt(x->r) + x->value;
    assert(x->zerocnt + x->onecnt == x->cnt);
    x->apply(1);
    x->apply(0);
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

void insert(pnode& x, int p)
{
    pnode l, r;
    split(x, l, r, p);
    pnode new_node = new node();
    merge(l, l, new_node);
    merge(x, l, r);
}

void xor_interval(pnode& x, int ql, int qr)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);
    mid->flip();
    merge(l, l, mid);
    merge(x, l, r);
}

void print(pnode x)
{
    push(x);
    if (!x) return;
    print(x->l);
    cout << x->value;
    print(x->r);
}

void rev(pnode& x, int ql, int qr)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);
    mid->reverse();
    merge(l, l, mid);
    merge(x, l, r);
}

void sort_interval(pnode& x, int ql, int qr)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);
    int num_ones = mid->onecnt;
    int num_zeros = mid->zerocnt;
    pnode midl, midr;
    split(mid, midl, midr, num_zeros);
    if (midl) midl->push_set_range(0);
    if (midr) midr->push_set_range(1);
    merge(midl, midl, midr);
    merge(l, l, midl);
    merge(x, l, r);
}

signed main()
{
    fast();


    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    pnode root = nullptr;
    repe(c, s) insert(root, 0);
    rep(i, n)
    {
        if (s[i] == '1')
        {
            xor_interval(root, i, i);
        }
    }

    while (q--)
    {
        int t, l, r;
        cin >> t >> l >> r;
        l--; r--;
        if (t == 1)
        {
            xor_interval(root, l, r);
        }
        if (t == 2)
        {
            rev(root, l, r);
        }
        if (t == 3)
        {
            sort_interval(root, l, r);
        }
        cout << max(root->gmp(0), root->gmp(1)) << "\n";
    }

    return 0;
}
