#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

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
#endif

struct node
{
    int prio, cnt;
    p2 v;
    node* l = 0, * r = 0;
    node(p2 v) : v(v), prio(rand()), cnt(1) {}
};

typedef node* pnode;

int get_cnt(pnode x) { return x ? x->cnt : 0; }
void pull(pnode x)
{
    if (x) x->cnt = 1 + get_cnt(x->l) + get_cnt(x->r);
}

void split(pnode x, pnode& l, pnode& r, p2 by)
{
    if (!x) return void(l = r = 0);
    if (x->v >= by) split(x->l, l, x->l, by), r = x;
    else split(x->r, x->r, r, by), l = x;
    pull(x);
}

void merge(pnode& x, pnode l, pnode r)
{
    if (!l || !r) x = l ? l : r;
    else if (l->prio < r->prio) merge(r->l, l, r->l), x = r;
    else merge(l->r, l->r, r), x = l;
    pull(x);
}

int countless(pnode x, int score)
{
    if (!x) return 0;
    if (x->v.first < score) return 1 + get_cnt(x->l) + countless(x->r, score);
    else return countless(x->l, score);
}

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    map<string, int> pindex;
    vector<pnode> nodes(n, 0);
    pnode root = 0;
    rep(i, n)
    {
        nodes[i] = new node(p2(0, i));
        merge(root, root, nodes[i]);
    }

    rep(i, n)
    {
        string name;
        cin >> name;
        pindex[name] = sz(pindex);
    }

    while (q--)
    {
        char c;
        cin >> c;
        if (c=='!')
        {
            int cnt;
            cin >> cnt;
            rep(i, cnt)
            {
                string name;
                int score;
                cin >> name >> score;
                int ind = pindex[name];
                pnode l, mid, r;
                p2 p = nodes[ind]->v;
                split(root, l, r, p);
                split(r, mid, r, p2(p.first,p.second+1));
                merge(root, l, r);
                nodes[ind]->v.first += score;
                p = nodes[ind]->v;
                split(root, l, r, p);
                merge(l, l, nodes[ind]);
                merge(root, l, r);
            }
        }
        else
        {
            string name;
            cin >> name;
            int score = nodes[pindex[name]]->v.first;
            cout << countless(root, score)+1 << " " << score << "\n";
        }
    }

    return 0;
}
