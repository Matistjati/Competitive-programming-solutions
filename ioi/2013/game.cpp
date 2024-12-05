#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
//const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#else
#include "game.h"
#endif


long long gcd2(long long X, long long Y) {
    if (X == -1) return Y;
    if (Y == -1) return X;
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

struct tnode
{
    int cnt, prio;
    p2 c;
    ll v, acc;
    tnode *l=0, *r=0;
    tnode(ll v, p2 c) : v(v), acc(v), cnt(1), prio(rand()), c(c) {}
};

typedef tnode* pnode;

int get_cnt(pnode x) { return x ? x->cnt : 0; }
int get_acc(pnode x) { return x ? x->cnt : 0; }

void pull(pnode x)
{
    if (!x) return;
    x->cnt = 1 + get_cnt(x->l) + get_cnt(x->r);
    x->acc = x->v;
    if (x->l) x->acc = gcd2(x->acc, x->l->acc);
    if (x->r) x->acc = gcd2(x->acc, x->r->acc);
}

// first i nodes go to left
void split(pnode x, pnode& l, pnode& r, int i, int add = 0)
{
    if (!x) return void(l = r = 0);
    int real_i = get_cnt(x->l) + add;
    if (i <= real_i) split(x->l, l, x->l, i, add), r = x;
    else split(x->r, x->r, r, i, add + get_cnt(x->l) + 1), l = x;
    pull(x);
}

void merge(pnode& x, pnode l, pnode r)
{
    if (!l || !r) x = l ? l : r;
    else if (l->prio < r->prio) merge(r->l, l, r->l), x = r;
    else merge(l->r, l->r, r), x = l;
    pull(x);
}

// count number of nodes with c < key
int order_of_key(pnode x, p2 key)
{
    if (!x) return 0;
    if (x->c == key) return get_cnt(x->l);
    else if (x->c < key) return 1 + get_cnt(x->l) + order_of_key(x->r, key);
    else return order_of_key(x->l, key);
}

struct snode
{
    int l, r;
    snode* lc=0, * rc=0;
    pnode strip=0;

    snode(int l, int r) : l(l), r(r) {}

    void insert(int row, int column, ll k)
    {
        int ind = order_of_key(strip, p2(column, row));
        pnode l, mid, r;
        split(strip, l, r, ind);
        if (order_of_key(r, p2(column, row+1)))
        {
            split(r, mid, r, 1);
            mid->v = mid->acc = k;
        }
        else mid = new tnode(k, p2(column, row));
        merge(l, l, mid);
        merge(strip, l, r);
    }

    void update(int row, int column, ll k)
    {
        insert(row, column, k);
        if (l==r)
        {
            return;
        }
        int mid = (l + r) / 2;
        if (row <= mid)
        {
            if (!lc) lc = new snode(l, mid);
            lc->update(row, column, k);
        }
        else
        {
            if (!rc) rc = new snode(mid + 1, r);
            rc->update(row, column, k);
        }
    }

    ll query(int rowl, int rowr, int coll, int colr)
    {
        if (l > rowr || r < rowl)
        {
            return -1;
        }
        if (l >= rowl && r <= rowr)
        {
            int lind = order_of_key(strip, p2(coll, -1));
            int rind = order_of_key(strip, p2(colr + 1, -1));
            pnode l, mid, r;
            split(strip, mid, r, rind);
            split(mid, l, mid, lind);
            ll ret = -1;
            if (mid)
            {
                if (ret == -1) ret = mid->acc;
                else ret = gcd2(ret, mid->acc);
            }
            merge(l, l, mid);
            merge(strip, l, r);
            return ret;
        }
        ll ret = -1;
        if (lc) ret = gcd2(ret, lc->query(rowl, rowr, coll, colr));
        if (rc) ret = gcd2(ret, rc->query(rowl, rowr, coll, colr));
        return ret;
    }
};

snode* root;

int R, C;
void init(int r, int c) {
    R = r;
    C = c;
    root = new snode(0, R - 1);
}

void update(int P, int Q, long long K) {
    root->update(P, Q, K);
}

long long calculate(int P, int Q, int U, int V) {
    ll ret = root->query(P, U, Q, V);

    if (ret == -1) ret = 0;
    return ret;
}


//signed main()
//{
//    fast();
//
//    int r, c, q;
//    cin >> r >> c >> q;
//    init(r, c);
//    while (q--)
//    {
//        int t;
//        cin >> t;
//        if (t==1)
//        {
//            int a, b, c;
//            cin >> a >> b >> c;
//            update(a, b, c);
//        }
//        else
//        {
//            int a, b, c, d;
//            cin >> a >> b >> c >> d;
//            cout << calculate(a, b, c, d) << "\n";
//        }
//    }
//
//    return 0;
//}
