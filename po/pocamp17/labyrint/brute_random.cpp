#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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

string s;

struct UF {
    vi par;
    UF(int n) : par(n) {iota(all(par),0);}
    int find(int x) {return par[x]==x?x:par[x]=find(par[x]);}
    int merge(int a, int b) {
        par[a=find(a)]=par[b=find(b)];
        return a!=b;
    }
};

using gr = vector<array<int,3>>;
mt19937 rng(42);
gr gen_graph(int n) {
    
    while (true) {
        UF uf(n);
        vector<array<int,3>> adj(n);
        int ncomps = n;
        rep(col, 3) {
            vi perm(n);
            iota(all(perm),0);
            shuffle(all(perm),rng);
            vi perm2(n/2);
            repp(i,n/2,n) perm2[i-n/2]=i;
            shuffle(all(perm2),rng);
            rep(i,n/2) {
                int a = perm[i];
                int b = perm[perm2[i]];
                adj[a][col] = b;
                adj[b][col] = a;
                ncomps -= uf.merge(a,b);
            }
        }
        if (ncomps == 1) {
            return adj;
        }
    }
}

const int MAX_N=32, TRIALS_PER_N=10000;
using bs = bitset<MAX_N>;
vector<bs> B;
vector<char> pos;
p2 find_start_goal(gr& adj) {
    int n = sz(adj);
    array<vector<char>,3> tadj;
    fill(all(tadj),vector<char>(n));
    rep(i,n) rep(j,3) tadj[j][i] = adj[i][j];

    rep(i,n) B[i].reset();
    rep(i,n) pos[i]=i, B[i][i]=1;
    rep(i,sz(s)) {
        vector<char>& row = tadj[s[i]];
        rep(j,n) {
            pos[j] = row[pos[j]];
            B[j][pos[j]] = 1;
        }
    }
    bs curr;
    vector<char> vis(n);
    rep(i,n) {
        fill(all(vis),0);
        curr.reset();
        int node = i;
        while (1) {
            if (vis[node]) break;
            vis[node]=1;
            curr |= B[node];
            node = pos[node];
        }
        if (curr.count() != n) {
            int p;
            rep(j,n) if (curr[j]==0) p = j;
            return p2({i,p});
        }
    }
    return {-1,-1};
}

int main(int argc, char *argv[]) {
    cin.tie(0)->sync_with_stdio(0);
    if (argc < 2) {
        cout << "Must be called with n baseline";
        return 0;
    }

    B.resize(MAX_N);
    pos.resize(MAX_N);
    
    cin >> s;
    for (char& c : s) {
        if (c == 'R') c = 0;
        if (c == 'G') c = 1;
        if (c == 'B') c = 2;
    }

    stringstream arg1(argv[1]);
    int n;
    arg1 >> n;

    while (1) {
        cerr << "Trying n=" << n << '\n';
        rep(_, TRIALS_PER_N) {
            gr adj = gen_graph(n);
            auto [s,g] = find_start_goal(adj);
            
            if (g!=-1) {
                cout << n << ' ' << s << ' ' << g << '\n';
                rep(i,n) {
                    cout << adj[i][0] << ' ' << adj[i][1] << ' ' << adj[i][2] << '\n';
                }
                n -= 2;
            }
        }
    }
    
    return 0;
}
