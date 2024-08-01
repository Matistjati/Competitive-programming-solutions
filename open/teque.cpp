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
uniform_int_distribution<int> dist(0, int(1e9));
struct node
{
    int cnt, prio, value;
    node* l = 0, * r = 0;
    node(int value) : cnt(1), prio(dist(rng)), value(value) {}
};

typedef node* pnode;
int get_cnt(pnode x) { return x ? x->cnt : 0; }

void pull(pnode x)
{
    if (x) x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1;
}

void split(pnode x, pnode& l, pnode& r, int i, int add = 0)
{
    if (!x)
        return void(l = r = 0);
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

int get(pnode x, int i, int add = 0)
{
    int real_i = get_cnt(x->l) + add;
    if (i == real_i) return x->value;
    else if (i <= real_i) return get(x->l, i, add);
    else return get(x->r, i, add + get_cnt(x->l) + 1);
}

signed main()
{
    fast();

    int n;
    cin >> n;

    pnode root = 0;
    int s = 0;
    while (n--)
    {
        string t;
        cin >> t;
        if (t=="push_back")
        {
            s++;
            int v;
            cin >> v;
            pnode u = new node(v);
            merge(root, root, u);
        }
        if (t=="push_front")
        {
            s++;
            int v;
            cin >> v;
            pnode u = new node(v);
            merge(root, u, root);
        }
        if (t=="push_middle")
        {
            int v;
            cin >> v;
            int ind = (s + 1) / 2;
            pnode u = new node(v);
            pnode l, r;
            split(root, l, r, ind);
            merge(l, l, u);
            merge(root, l, r);
            s++;
        }
        if (t=="get")
        {
            int i;
            cin >> i;
            cout << get(root, i) << "\n";
        }
    }

    return 0;
}
