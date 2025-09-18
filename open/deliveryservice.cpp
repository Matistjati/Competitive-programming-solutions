#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repp(i, a, b) for(int i = a; i < (b); i++)
#define rep(i, a) for(int i = 0; i < (a); i++)
#define repe(i, x) for (auto& i : x)
#define all(x) begin(x), end(x)
#define sz(x) ((ll)(x).size())
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> pii;
typedef pair<int,int> p2;

struct UF
{
    ll total_con_pairs = 0;
    vi par;
    vector<set<int>> comp;
    vector<set<int>> comp_unique;
    map<p2,ll> isect_count;
    p2 normalize(int a, int b)
    {
        return p2(min(a,b),max(a,b));
    }
    UF(int n) : par(n),comp(n),comp_unique(n)
    {
        rep(i,n)par[i]=i;
        rep(i,n)comp_unique[i].insert(i/2);
        rep(i,n)comp[i].insert(i);
        rep(i,n) isect_count[normalize(2*i,2*i+1)]++;
    }
    int find(int x)
    {
        return par[x]==x?x:par[x]=find(par[x]);
    }
    
    void merge(int a, int b)
    {
        a=find(a);
        b=find(b);
        if (a==b) return;
        if (sz(comp[a])<sz(comp[b])) swap(a,b);
        total_con_pairs -= sz(comp_unique[a])*(sz(comp_unique[a])-1)/2;
        total_con_pairs -= sz(comp_unique[b])*(sz(comp_unique[b])-1)/2;
        repe(u,comp[b])
        {
            comp[a].insert(u);
            int cu = find(u);
            int cmu = find(u^1);
            if (cu==cmu)continue;
            total_con_pairs += --isect_count[normalize(cu,cmu)];

            if (cmu!=a)
            {
                // cout << "mirror comp: " << cmu << " " << a << ", isect count:" << isect_count[normalize(a,cmu)] << '\n';
                total_con_pairs -= isect_count[normalize(a,cmu)]++;
            }
        }
        repe(u,comp_unique[b])
        {
            comp_unique[a].insert(u);
        }
        par[b]=a;
        total_con_pairs += sz(comp_unique[a])*(sz(comp_unique[a])-1)/2;

    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    //cin.exceptions(cin.failbit);
    int n,m;
    cin >> n >> m;

    UF uf(2*n);
    rep(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;

        uf.merge(2*a,2*b+1);
        cout << uf.total_con_pairs << '\n';
    }
}
