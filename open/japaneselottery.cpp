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

const int BLOCKSIZE = 500;
int main() {
    int w,h,q;
    cin >> w >> h >> q;
    int num_blocks = (h+BLOCKSIZE-1)/BLOCKSIZE;
    vector<vector<p2>> blocks(num_blocks, vector<p2>(BLOCKSIZE, p2(0,0)));
    vvi perms(num_blocks);
    rep(i,num_blocks)
    {
        vi perm(w);
        rep(j,w) perm[j]=j;
        perms[i]=perm;
    }

    int howmanyactive = 0;

    auto rebuild_block = [&](int block_ind, int who, p2 swa)
    {
        vector<p2>& block = blocks[block_ind];
        if (block[who]==p2(0,0))
        {
            howmanyactive++;
            block[who]=swa;
        }
        else block[who]=p2(0,0), howmanyactive--;

        vi perm(w);
        rep(i,w) perm[i]=i;

        for (auto [i,j] : block)
        {
            swap(perm[i],perm[j]);
        }

        perms[block_ind] = perm;
    };
    
    while (q--)
    {
        int y,a,b;
        cin >> y >> a >> b;
        y--; a--; b--;

        int block_ind = y / BLOCKSIZE;
        rebuild_block(block_ind, y % BLOCKSIZE, p2(a,b));

        vi perm(w);
        rep(i,w) perm[i]=i;

        vi t = perm;
        repe(p, perms)
        {

            rep(i,w)
            {
                t[i] = perm[p[i]];
            }
            perm = t;
        }

        int num_cycles = 0;
        vi vis(w);
        rep(i,w) {
            if (vis[i]) continue;
            int x = i;
            num_cycles++;
            x = perm[x];
            while (x != i) {
                vis[x] = 1;
                x = perm[x];
            }
        }
        cout << (w - num_cycles) << '\n';
    }

    return 0;
}

