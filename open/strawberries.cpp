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


int knapsack(vi w, int t) {
	int a = 0, b = 0, x;
	while (b < sz(w) && a + w[b] <= t) a += w[b++];
	if (b == sz(w)) return a;
	int m = *max_element(all(w));
	vi u, v(2*m, -1);
	v[a+m-t] = b;
	repp(i,b,sz(w)) {
		u = v;
		repp(x,0,m) v[x+w[i]] = max(v[x+w[i]], u[x]);
		for (x = 2*m; --x > m;) repp(j, max(0LL,u[x]), v[x])
			v[x-w[j]] = max(v[x-w[j]], j);
	}
	for (a = t; v[a+m-t] < 0; a--) ;
	return a;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int box = 1;
    while (1) {
        array<int,10> cnt;
        rep(i,10) cin >> cnt[i];
        if (accumulate(all(cnt),0)==0) break;

        int val;
        int tot = 0;
        vi wt;
        rep(val,10) {
            rep(j,cnt[val]) {
                wt.push_back(val+1);
                tot += val+1;
            }
        }
        cout << "Box #" << box << ":\n";
        if (tot%2==0 && knapsack(wt, tot/2)==tot/2) cout << "Can";
        else cout << "Can't";
        cout << " be divided.\n";
        box++;
    }
    
    return 0;
}
