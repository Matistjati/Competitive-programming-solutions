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

int binpow(int a, int b, int p)
{
    int ret = 1;
    int d = a;
    while (b)
    {
        if (b % 2) ret = (ret * d) % p;
        b >>= 1;
        d = (d * d) % p;
    }
    return ret;
}

vi powers[2];
vi invpowers[2];
int mod[2];
void init_hash(int n)
{
    n += 10;
    powers[0].resize(n);
    powers[1].resize(n);
    invpowers[0].resize(n);
    invpowers[1].resize(n);
    mod[0] = 1e9 + 7;
    mod[1] = 1e9 + 9;
    powers[0][0] = 1;
    powers[1][0] = 1;
    powers[0][1] = dist(rng) % 10000 + 255;
    powers[1][1] = dist(rng) % 10000 + 255;
    rep(d, 2) repp(i, 2, n)
    {
        powers[d][i] = (powers[d][i - 1] * powers[d][1]) % mod[d];
    }
    rep(d, 2) rep(i, n)
    {
        invpowers[d][i] = binpow(powers[d][i], mod[d] - 2, mod[d]);
    }
}

struct dual_hash
{
    p2 h;
    dual_hash(char c, int p)
    {
        h = p2((c * powers[0][p]) % mod[0], (c * powers[1][p]) % mod[1]);
    }
    dual_hash(int a, int b) : h(a% mod[0], b% mod[1]) {}
    dual_hash() {}

    dual_hash operator+(const dual_hash& other)
    {
        return dual_hash(h.first + other.h.first, h.second + other.h.second);
    }
    dual_hash operator*(const dual_hash& other)
    {
        return dual_hash(h.first * other.h.first, h.second * other.h.second);
    }
};


struct node
{
    int cnt, prio;
    char c;
    dual_hash hash_v, hash_accum, lazy;

    node* l, * r;
    node(char c, int p) : cnt(1), prio(dist(rng)), c(c), l(nullptr), r(nullptr)
    {
        hash_v = dual_hash(c, p);
        hash_accum = dual_hash(c, p);
        lazy = dual_hash(1LL, 1LL);
    }
};

typedef node* pnode;
int get_cnt(pnode x) { return x ? x->cnt : 0; }
dual_hash get_hash_ac(pnode x) { return x ? x->hash_accum : dual_hash(0LL, 0LL); }

void pull(pnode x)
{
    if (x)
    {
        x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1;
        x->hash_accum = get_hash_ac(x->l) + get_hash_ac(x->r) + x->hash_v;
    }
}

void push(pnode x)
{
    if (x)
    {
        dual_hash l = x->lazy;
        x->lazy = dual_hash(1LL, 1LL);
        if (x->l)
        {
            x->l->hash_accum = x->l->hash_accum * l;
            x->l->hash_v = x->l->hash_v * l;
            x->l->lazy = x->l->lazy * l;
        }
        if (x->r)
        {
            x->r->hash_accum = x->r->hash_accum * l;
            x->r->hash_v = x->r->hash_v * l;
            x->r->lazy = x->r->lazy * l;
        }
    }
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

void lazy_mul(pnode& x, dual_hash mul)
{
    if (!x) return;
    x->lazy = x->lazy * mul;
    x->hash_accum = x->hash_accum * mul;
    x->hash_v = x->hash_v * mul;
}

void insert(pnode& x, int p, char c)
{
    pnode l, r;
    split(x, l, r, p);
    pnode new_node = new node(c, p);
    lazy_mul(r, dual_hash(powers[0][1], powers[1][1]));
    merge(l, l, new_node);
    merge(x, l, r);
}

void print(pnode x)
{
    if (!x) return;
    print(x->l);
    cout << x->hash_accum.h.first << " ";
    print(x->r);
}

int tree_sz = 0;
dual_hash query(pnode& x, int ql, int qr)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);
    dual_hash ret = mid->hash_accum;
    ret = ret * dual_hash(invpowers[0][ql], invpowers[1][ql]);
    merge(l, l, mid);
    merge(x, l, r);
    dual_hash h = dual_hash(ret.h.first * 1, ret.h.second * 1);
    return h;
}

void del(pnode& x, int ql, int qr)
{
    pnode l, mid, r;
    split(x, l, r, qr + 1);
    split(l, l, mid, ql);
    int d = qr - ql + 1;
    lazy_mul(r, dual_hash(invpowers[0][d], invpowers[1][d]));
    merge(x, l, r);
}

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    init_hash(n + q);
    tree_sz = n;

    string s;
    cin >> s;
    pnode root = nullptr;
    pnode rootr = nullptr;
    rep(i, n) insert(root, i, s[i]);
    reverse(all(s));
    rep(i, n) insert(rootr, i, s[i]);

    rep(i, q)
    {
        int t;
        cin >> t;
        if (t == 2)
        {
            char c;
            int l;
            cin >> c >> l;
            l--;
            insert(root, l, c);
            l = tree_sz - l;
            insert(rootr, l, c);
            tree_sz++;
        }
        else if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            l--; r--;
            int d = r - l + 1;
            del(root, l, r);
            r = tree_sz - 1 - l;
            l = r - d + 1;
            del(rootr, l, r);
            tree_sz -= d;

        }
        else if (t == 3)
        {
            int l, r;
            cin >> l >> r;
            l--; r--;
            dual_hash a = query(root, l, r);
            int x = tree_sz - 1 - l - r;
            l += x;
            r += x;
            dual_hash b = query(rootr, l, r);
            cout << (a.h == b.h ? "yes" : "no") << "\n";
        }
    }


    return 0;
}
