#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

struct UF {
    vi par;
    UF(int n) : par(n) {
        iota(all(par),0);
    }
    int find(int x) {return par[x]==x?x:par[x]=find(par[x]);}
    void merge(int a, int b) {
        a=find(a); b=find(b);
        par[b]=a;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,k;
    cin >> n >> k;
    vi nums(n);
    rep(i,n) cin >> nums[i];
    
    UF uf(n);
    rep(i,n) rep(j,n) if (nums[i] % k == nums[j] % k) uf.merge(i,j);

    map<int,map<int,int>> occs;
    map<int,vi> inds;
    rep(i,n) {
        occs[uf.find(i)][nums[i]]++;
        inds[uf.find(i)].push_back(i);
    }

    vi snums(nums);
    sort(all(snums));

    bool good = 1;

    for (auto [head, ind] : inds) {
        map<int,int> mydist = occs[head];
        map<int,int> goaldist;
        repe(i, ind) {
            goaldist[snums[i]]++;
        }

        for (auto [key, val] : goaldist) {
            good &= mydist[key] == val;
        }
    }

    cout << (good ? "YES" : "NO") << '\n';

    return 0;
}
