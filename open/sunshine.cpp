// very weird and overcomplicated solution
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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

mt19937 rng;
uniform_int_distribution<int> dist(0, int(1e9));
struct node
{
    int cnt, prio;
    double value;
    double lazyadd, lazymul;
    node* l = 0, * r = 0;
    node(double value) : cnt(1), prio(dist(rng)), value(value), lazyadd(0),lazymul(1) {}
};

typedef node* pnode;
int get_cnt(pnode x) { return x ? x->cnt : 0; }
void apply_add(pnode x, double a)
{
    x->value += a;
    x->lazyadd += a;
}

void apply_mul(pnode x, double m)
{
    x->value *= m;
    x->lazyadd *= m;
    x->lazymul *= m;
}

void push(pnode x)
{
    if (!x) return;
    if (x->l) apply_mul(x->l, x->lazymul);
    if (x->r) apply_mul(x->r, x->lazymul);
    x->lazymul = 1;
    if (x->l) apply_add(x->l, x->lazyadd);
    if (x->r) apply_add(x->r, x->lazyadd);
    x->lazyadd = 0;
}

void pull(pnode x)
{
    if (x) x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1;
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

double get_value(pnode& x, int i, int add = 0)
{
    push(x);
    int real_i = get_cnt(x->l) + add;
    if (i == real_i) return x->value;
    else if (i <= real_i) return get_value(x->l, i, add);
    else return get_value(x->r, i, add + get_cnt(x->l) + 1);
}

void set_value(pnode& x, int i, double v, int add = 0)
{
    push(x);
    int real_i = get_cnt(x->l) + add;
    if (i == real_i) x->value = v;
    else if (i <= real_i) set_value(x->l, i, v, add);
    else set_value(x->r, i, v, add + get_cnt(x->l) + 1);
}

void reset(pnode x, double value)
{
    x->l = x->r = 0;
    x->lazyadd = 0;
    x->lazymul = 1;
    x->value = value;
    x->cnt = 1;
}


pnode build(int x, int l, int r, double v)
{
    if (l > r) return 0;
    if (r < l) return 0;
    if (l == r)
    {
        pnode ret = new node(v);
        ret->prio = int(5e5) - x;
        return ret;
    }
    int mid = (l + r) / 2;
    pnode ret = new node(v);
    ret->prio = int(5e5)-x;
    ret->l = build(x*2,l, mid - 1, v);
    ret->r = build(x*2+1,mid + 1, r, v);
    pull(ret);
    return ret;
}

double ans(int n, int t, vector<double>& prob)
{
    pnode root[2] = { build(1,0,t,0),build(1,0,t,1)};



    for (int i = n - 1; i >= 0; --i) {
        double zero0 = (1 - prob[i]) * get_value(root[0], 0);
        double zero1 = (1 - prob[i]) * get_value(root[1], 0);
        
        double dp1t = get_value(root[1], t);
        {
            pnode l, r;
            split(root[1], l, r, 1);
            // discard l
            apply_mul(r, prob[i]);
            apply_add(r, zero1);

            reset(l, zero1 + prob[i] * dp1t);
            merge(root[1], r, l);

        }
    
        {
            pnode l, mid, r;
            split(root[0], l, r, t);
            split(l, l, mid, 1);
            // discard l, r
            apply_mul(mid, prob[i]);
            apply_add(mid, zero0);

            reset(l, zero0 + prob[i] * dp1t);
            reset(r, zero0 + prob[i] * dp1t);
            merge(mid, mid, l);
            merge(root[0], mid, r);
        }
    }

    return get_value(root[0], 0);
}


double nkdp(int n, int t, vector<double>& prob)
{
    vector<vector<double>> dp(2, vector<double>(t + 1));

    rep(k, t + 1) dp[1][k] = 1;

    for (int i = n - 1; i >= 0; --i) {
        double zero0 = (1 - prob[i]) * dp[0][0];
        double zero1 = (1 - prob[i]) * dp[1][0];


        rep(k, t) {
            dp[1][k] = zero1 + prob[i] * dp[1][k + 1];
        }
        rep(k, t - 1)
        {
            dp[0][k] = zero0 + prob[i] * dp[0][k + 1];
        }
        dp[0][t - 1] = zero0 + prob[i] * dp[1][t];
        dp[0][t] = zero0 + prob[i] * dp[1][t];
        dp[1][t] = zero1 + prob[i] * dp[1][t];
    }

    return dp[0][0];
}


signed main()
{
    fast();

    int n, k;
    cin >> n >> k;

    vector<double> prob(n);
    rep(i, n)
    {
        cin >> prob[i];
    }

    if (k<=10)
    {
        cout << nkdp(n, k, prob);
    }
    else cout << ans(n, k, prob);

    return 0;
}
