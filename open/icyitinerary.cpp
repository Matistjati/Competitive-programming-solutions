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

struct Node
{
    int i;
    Node* l=0, * r=0;
    Node(int i) : i(i) {}
};

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;

    set<p2> edges;
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges.emplace(a,b);
        edges.emplace(b,a);
    }

    if (n==2)
    {
        cout << "1 2";
        return 0;
    }

    vector<Node*> nodes(n);
    rep(i, n)nodes[i] = new Node(i);

    Node* l=0,*r=0;

    auto e = [&](int a, int b)
        {
            return edges.count(p2(a, b));
        };

    auto mate = [&](Node* a, Node* b)
        {
            a->r = b;
            b->l = a;
        };

    repp(i, 1, n)
    {
        Node* u = nodes[i];
        if (l==0&&r==0)
        {
            l = u;
        }
        else if (l==0&&r!=0)
        {
            mate(u, r);
            if (e(i, r->i))
            {
                l = r;
                r = l->r;
            }
            else
            {
                r = u;
            }
        }
        else if (l != 0 && r == 0)
        {
            mate(l, u);
            if (e(i, l->i))
            {
                l = u;
            }
            else
            {
                r = u;
            }
        }
        else
        {
            bool a = e(l->i, i);
            bool b = e(r->i, i);
            if (a&&b)
            {
                mate(l, u);
                mate(u, r);
                l = r;
                r = l->r;
            }
            else if (!a && b)
            {
                if (!l->l)
                {
                    mate(u, l);
                    mate(l, r);
                    r = u;
                    l = 0;
                }
                else
                {
                    Node* ll = l->l;
                    bool c = e(ll->i, i);
                    if (c)
                    {
                        mate(ll, u);
                        mate(u, l);
                        l = u;
                        r = u->r;
                    }
                    else
                    {
                        mate(ll, u);
                        mate(u, l);
                        l = ll;
                        r = u;
                    }
                }
            }
            else if (!a && !b)
            {
                mate(l, u);
                mate(u, r);
                r = u;
            }
            else if (a && !b)
            {
                mate(l, u);
                mate(u, r);
                l = u;
            }
        }
    }
    if (!l) l = r;
    if (!r) r = l;
    while (l->l) l = l->l;
    while (r->r) r = r->r;
    vi ans;

    if (e(0,l->i))
    {
        mate(nodes[0], l);
        l = nodes[0];
        while (l)
        {
            ans.push_back(l->i);
            l = l->r;
        }
    }
    else if (!e(0,r->i))
    {
        mate(r, nodes[0]);
        r = nodes[0];
        while (r)
        {
            ans.push_back(r->i);
            r = r->l;
        }
    }
    else
    {
        if (e(l->i,r->i))
        {
            r->l->r = 0;
            mate(nodes[0], r);
            mate(r, l);
            l = nodes[0];
            while (l)
            {
                ans.push_back(l->i);
                l = l->r;
            }
        }
        else
        {
            l->r->l = 0;
            mate(r, l);
            mate(l, nodes[0]);
            r = nodes[0];
            while (r)
            {
                ans.push_back(r->i);
                r = r->l;
            }
        }
    }
    repe(u, ans) cout << u+1 << " ";
    cout << '\n';

    return 0;
}
