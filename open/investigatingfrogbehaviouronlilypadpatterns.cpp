#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = ll(1e18);
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll,ll>;

#define rep(i,b) for(int i = 0; i < (b); i++)
#define repp(i,a,b) for(int i = (a); i < (b); i++)
#define repe(i,a) for(auto& i : a)
#define sz(x) ((int)x.size())

struct Tree
{
    vector<int> tree;
    Tree(int n) : tree(n*4) {}

    void update(int x, int l, int r, int i, int v)
    {
        if (l==r) return void(tree[x]=v);
        int mid = (l+r)/2;
        if (i<=mid) update(x*2,l,mid,i,v);
        else update(x*2+1,mid+1,r,i,v);
        tree[x]=tree[x*2]+tree[x*2+1];
    }

    int monotone_one(int x, int l, int r)
    {
        return tree[x] == r-l+1;
    }

    int internal_search(int x, int l, int r)
    {
        if (l==r)
        {
            return l;
        }
        int mid = (l+r)/2;
        if (!monotone_one(x*2,l,mid)) return internal_search(x*2,l,mid);
        return internal_search(x*2+1,mid+1,r);
    }

    int leftmost_zero(int x, int l, int r, int ql) // leftmost zero with l>=ql
    {
        if (r<ql) return -1;
        if (l>=ql)
        {
            if (monotone_one(x,l,r)) return -1;
            return internal_search(x,l,r);
        }
        int mid = (l+r)/2;
        int ret = leftmost_zero(x*2,l,mid,ql);
        if (ret!=-1) return ret;
        return leftmost_zero(x*2+1,mid+1,r,ql);
    }
};

const int treesize = int(2e6);
int main() {
    Tree tree(treesize);
    int n;
    cin >> n;
    vi pos(n);
    rep(i,n)
    {
        int x;
        cin >> x;
        pos[i]=x-1;
        tree.update(1,0,treesize,x-1,1);
    }
    int q;
    cin >> q;
    while (q--)
    {
        int k;
        cin >> k;
        k--;
        int ind = pos[k];
        int new_spot = tree.leftmost_zero(1,0,treesize,ind);
        tree.update(1,0,treesize,ind,0);
        tree.update(1,0,treesize,new_spot,1);
        pos[k] = new_spot;
        cout << new_spot+1 << '\n';
    }

    return 0;
}
