#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
const ll inf = 1e18;
#define sz(x) ((ll)x.size())
#define all(x) begin(x),end(x)
using vi = vector<ll>;

bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
        if (btoa[j] == -1) return 1;
        vis[j] = 1; int di = btoa[j];
        for (int e : g[di])
                if (!vis[e] && find(e, g, btoa, vis)) {
                        btoa[e] = di;
                        return 1;
                }
        return 0;
}
int dfsMatching(vector<vi>& g, vi& btoa) {
        vi vis;
        rep(i,sz(g)) {
                vis.assign(sz(btoa), 0);
                for (int j : g[i])
                        if (find(j, g, btoa, vis)) {
                                btoa[j] = i;
                                break;
                        }
        }
        return sz(btoa) - (int)count(all(btoa), -1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    bitset<int(2e7)+20> isprime;
    isprime = ~isprime;
    repp(i,2,isprime.size()) {
        if (!isprime[i]) continue;
        for (int j = i + i; j < sz(isprime); j+=i) {
            isprime[j]=0;
        }
    }

    int n;
    cin >> n;
    vector<int> cicada(n);
    rep(i,n) cin >> cicada[i];
    while (count(all(cicada),1)>1) cicada.erase(find(all(cicada),1));
    n=sz(cicada);
    int evencnt=0,oddcnt=0;
    vi myind(n);
    rep(i,n) {
        int c = cicada[i];
        if (c%2==1) {
            myind[i] = oddcnt++;
        }
        else {
            myind[i]=evencnt++;
        }
    }
    vector<vi> adj(evencnt);
    rep(i,n) {
        if (cicada[i] % 2 ==1) continue;
        rep(j,n) {
            if (isprime[cicada[i]+cicada[j]]) {
                adj[myind[i]].push_back(myind[j]);
            }
        }
    }

    vi btoa(oddcnt,-1);
    int ans = n-dfsMatching(adj,btoa);

    cout << ans << '\n';

    return 0;
}
