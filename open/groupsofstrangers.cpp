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


struct TwoSat {
	int N;
	vector<vi> gr;
	vi values; // 0 = false, 1 = true

	TwoSat(int n = 0) : N(n), gr(2*n) {}

	int addVar() { // (optional)
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}

	void imply(int a, int b) { // a => b
		a = max(2*a+1, ~a*2), b = max(2*b+1, ~b*2);
		gr[a].push_back(b);
		gr[b^1].push_back(a^1);
	}
	void either(int a, int b) { imply(~a, b); }
	void setValue(int x) { imply(~x, x); }

	void atMostOne(const vi& li) { // (optional)
		int cur = sz(li) ? li[0] : 0;
		repp(i,1,sz(li)) {
			int next = addVar();
			imply(cur, ~li[i]);
			imply(cur, next);
			imply(li[i], next);
			cur = next;
		}
	}

	vi val, z; int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x; z.push_back(i);
		for (int e : gr[i]) low = min<int>(low, val[e] ?: dfs(e));
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			val[x] = INT_MAX - low;
			values[x>>1] = !(x&1);
		} while (x != i);
		return low;
	}

	bool solve() {
		values.assign(N, 0); val.assign(2*N, 0);
		rep(i,2*N) if (!val[i]) dfs(i);
		rep(i,N) if (val[2*i] == val[2*i+1]) return 0;
		return 1;
	}
};

const int MAXN = 1000;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n,m;
    cin >> n >> m;

    using bset = bitset<MAXN>;
    vector<bset> adj(n);
    vector<vector<short>> nadj(n);
    rep(i,m) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        adj[a][b]=1;
        adj[b][a]=1;
        nadj[a].push_back(b);
        nadj[b].push_back(a);
    }

    rep(i,n) {
        // low degree
        if (adj[i].count() > 15) continue;
    
        // find reduced HR
        vector<int> neigh;
        for (int j = adj[i]._Find_first(); j < n; j = adj[i]._Find_next(j)) {
            neigh.push_back(j);
        }

        int k = sz(neigh);
        assert(sz(neigh)<=15);
        int bestmask = (1<<30)-1;
        bset neigh_mask;
        repe(u,neigh) neigh_mask[u]=1;
        rep(mask,1<<k) {
            if (__builtin_popcount(mask) >= __builtin_popcount(bestmask)) continue;
            bset cover = neigh_mask;
            rep(i,k) if (mask & (1<<i)) cover |= adj[neigh[i]];
            if (cover.count() == n) {
                bestmask = mask;
            }
        }
        if (__builtin_popcount(bestmask) > 8) continue;
        vector<int> hr;
        rep(i,k) if (bestmask&(1<<i)) hr.push_back(neigh[i]);

        // we have our HR: can now solve using 2SAT

        // ceo is color 0
        sort(all(hr));
        int ceo = i;
        vector<char> color(n,-1),color2(n,-1);
        auto try_mask = [&](int mask) {
            vector<char> is_special(n);
            is_special[ceo]=1;
            color.assign(n,-1);
            color2.assign(n,-1);
            color[ceo]=0;
            rep(i,sz(hr)) {
                is_special[hr[i]]=1;
                if (mask&(1<<i)) color[hr[i]]=1;
                else color[hr[i]]=2;
            }
            vector<array<char,3>> colors_avail(n, {1,1,1});

            rep(i,n) {
                if (is_special[i]) continue;
                for (auto h : hr) {
                    if (adj[i][h]) {
                        colors_avail[i][color[h]]=0;
                    }
                }
                if (adj[ceo][i]) colors_avail[i][0]=0;
                vector<char> cols;
                rep(j,3) if (colors_avail[i][j]) cols.push_back(j);
                if (cols.empty()) return;
                assert(sz(cols)<=2);
                color[i]=cols[0];
                if (sz(cols)>1) color2[i]=cols.back();
            }

            TwoSat sat(n);
            rep(i,n) {
                if (color2[i]==-1) {
                    sat.imply(i,~i);
                }
                assert(color[i]!=-1);
                repe(e,nadj[i]) {
                    { // i dont switch
                        if (color[i]==color[e]) sat.imply(~i,e);
                        if (color[i]==color2[e]) sat.imply(~i,~e);
                    }
                    if (color2[i]!=-1)
                    { // i do switch
                        if (color2[i]==color[e]) sat.imply(i,e);
                        if (color2[i]==color2[e]) sat.imply(i,~e);
                    }
                }
            }
            if (sat.solve()) {
                rep(i,n) {
                    int c = sat.values[i] ? color2[i] : color[i];
                    cout << c+1 << ' ';
                }
                cout << '\n';
                exit(0);
            }
        };
        rep(mask,1<<sz(hr)) {
            try_mask(mask);
        }
        cout << "Impossible\n";
        return 0;
    }

    assert(0);

    return 0;
}
