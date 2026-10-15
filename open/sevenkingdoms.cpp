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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n,m;
    cin >> n >> m;


    using bset = bitset<2000>;
    vector<bset> adj(n);
    rep(i,m) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        adj[a][b]=1;
        adj[b][a]=1;
    }

    vector<char> color(n);
    rep(i,n) {
        if (adj[0][i]) color[i]=0;
        else if (adj[1][i]) color[i]=1;
        else color[i]=2;
    }
    color[0]=3;
    color[1]=4;

    TwoSat sat(n);
    rep(i,n) {
        rep(j,n) {
            if (i==j) continue;
            if (color[i] == 2 && color[j]==2 && !adj[i][j]) {
                cout << "impossible\n";
                return 0;
            }
        }

        bool can_switch = color[i]==0 || color[i]==1;
        rep(j,n) {
            if (i==j) continue;
            if (color[j]==2) can_switch &= adj[i][j];
        }
        if (!can_switch) sat.imply(i, ~i);

        rep(j,n) {
            if (i==j) continue;
            if ((color[i]==0 || color[i]==1) && color[i]==color[j]) {
                if (!adj[i][j]) {
                    sat.imply(i,~j);
                    sat.imply(~i,j);
                }
            }
            if (color[i]==0 && color[j]==1) {
                if (!adj[i][j]) {
                    sat.imply(i,~j);
                    sat.imply(j,~i);
                }
            }
        }
    }

    if (sat.solve()) {
        cout << "1 ";
        rep(i,n) if (color[i]==0 && !sat.values[i]) cout << i+1 << ' ';
        cout << '\n';
        cout << "2 ";
        rep(i,n) if (color[i]==1 && !sat.values[i]) cout << i+1 << ' ';
        cout << '\n';
    }
    else {
        cout << "impossible\n";
    }


    return 0;
}
