#include <bits/stdc++.h>
using namespace std;

//typedef long long ll;
//#define int ll
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
    char c;
    int cnt, prio;
    node *l, *r;
    node(char c) : cnt(1), c(c), prio(dist(rng)), l(nullptr), r(nullptr) {}
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
        return void(l = r = nullptr);
    int real_i = add + get_cnt(x->l);
    if (i <= real_i)
        split(x->l, l, x->l, i, add), r = x;
    else
        split(x->r, x->r, r, i, add + get_cnt(x->l)+1), l = x;
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

void print(pnode x)
{
    if (!x) return;
    print(x->l);
    cout << x->c;
    print(x->r);
}


signed main()
{
    fast();

    string s;
    cin >> s;

    pnode root = nullptr;
    int cursor = 0;
    repe(c, s)
    {
        if (c=='L')
        {
            cursor--;
        }
        else if (c=='R')
        {
            cursor++;
        }
        else if (c=='B')
        {
            pnode l, _, r;
            split(root, l, r, cursor);
            split(l, l, _, cursor - 1);
            merge(root, l, r);
            cursor--;
        }
        else
        {
            pnode new_node = new node(c);
            pnode l, r;
            split(root, l, r, cursor);
            merge(l, l, new_node);
            merge(root, l, r);
            cursor++;
        }
    }
    print(root);

    return 0;
}
