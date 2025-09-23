using namespace std;
#include <bits/stdc++.h>


using ll = long long;

using vi = vector<int>;

#define rep(i,b) for (int i = 0; i < (b); i++)
#define repp(i,a,b) for (int i = (a); i < (b); i++)

struct UF
{
    vi par,size;
    UF(int n) : par(n), size(n,1)
    {
        rep(i,n)par[i]=i;
    }
    int find(int x) {return par[x]==x?x:par[x]=find(par[x]);}
    void merge(int a, int b)
    {
        a=find(a);b=find(b);
        if(a==b) return;
        if (size[a]<size[b]) swap(a,b);
        par[b]=a;
        size[a]+=size[b];
    }
};

int main() {
    int n,m;
    cin >> n >> m;
    UF uf(n);

    rep(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        uf.merge(a,b);
    }

    int ans = 0;
    rep(i,n) ans=max(ans,uf.size[i]);
    cout << ans << '\n';

    return 0;

}

