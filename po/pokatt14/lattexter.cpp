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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int BIG = int(2e18);

struct node
{
    int ccnt, ind;
    string leaf;
    node* l=0, * r=0;
    node(string leaf, int ind) : leaf(leaf), ccnt(sz(leaf)), ind(ind) {}
    bool l_big() { return l->ccnt > r->ccnt; }
    bool is_leaf() { return sz(leaf); }

    node(node* l, node* r, int ind) : l(l), r(r), ind(ind)
    {
        int s = l->ccnt + r->ccnt;
        if (s >= BIG) s = BIG;
        ccnt = s;
    }
};

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    vector<node*> nodes(n, 0);
    rep(i, n)
    {
        int t;
        cin >> t;
        if (t==0)
        {
            string s;
            cin >> s;
            nodes[i] = new node(s, i);
        }
        else
        {
            int a, b;
            cin >> b;
            t--; b--;
            if (nodes[t]->ccnt == BIG) nodes[i] = nodes[t];
            else nodes[i] = new node(nodes[t], nodes[b], i);
        }
    }

    // solution: every node has a directed edge to its larger subtree
    // this is basically heavy-light decomposition, but because multiple nodes
    // can point to same node, it's a tree. however, by the same argument,
    // we only switch tree log(N) times.
    // how do we quickly go forward in a tree? binary lifting!
    // we want to keep going in one tree for some interval, then switch
    // O(nlog(n)+qlog(n)^2)
    // implementation details left as exercise for reader
    node* down[20][int(5e5)];
    int l_ignore[20][int(5e5)];
    rep(i, n)
    {
        node* u = nodes[i];
        if (u->is_leaf())
        {
            down[0][i] = u;
            l_ignore[0][i] = 0;
        }
        else
        {
            down[0][i] = u->l_big() ? u->l : u->r;
            l_ignore[0][i] = u->l_big() ? 0 : u->l->ccnt;
        }
        repp(d, 1, 20)
        {
            int downer = down[d-1][i]->ind;
            down[d][i] = down[d-1][downer];
            l_ignore[d][i] = l_ignore[d-1][i] + l_ignore[d-1][downer];
            l_ignore[d][i] = min(l_ignore[d][i], BIG);
        }
    }

    rep(ind, q)
    {
        int p;
        cin >> p;
        p--;
        
        node* curr = nodes.back();
        while (!curr->is_leaf())
        {
            node* u = curr;
            for (int d = 19; d >= 0; d--)
            {
                node* downer = down[d][u->ind];
                int l = l_ignore[d][u->ind];
                int r = l + downer->ccnt;
                if (p>=l&&p<r)
                {
                    p -= l;
                    u = downer;
                }
            }

            curr = u;
            if (curr->is_leaf()) break;
            if (p < curr->l->ccnt)
            {
                curr = curr->l;
            }
            else
            {
                p -= curr->l->ccnt;
                curr = curr->r;
            }
        }
        cout << curr->leaf[p];
    }


    return 0;
}
