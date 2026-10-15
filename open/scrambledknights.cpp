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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n;
    cin >> n;

    vi a(n),b(n);
    rep(i,n) cin >> a[i],a[i]--;
    rep(i,n) cin >> b[i],b[i]--;

    cout << "5\n";

    auto solve = [&](vi& arr, vi& brr) {
        vi loc(n);
        rep(i,n) loc[arr[i]]=i;
        int x = n/4;
        auto clean = [&](vi qu) {
            sort(all(qu));
            qu.erase(unique(all(qu)),qu.end());
            int orig = sz(qu);
            rep(i,n) {
                if (sz(qu) < n/2 && !binary_search(begin(qu),begin(qu)+orig,i)) {
                    qu.push_back(i);
                }
            }
            sort(all(qu));
            repe(v,qu) cout << v+1 << ' ';
            cout << '\n';

            {
                vi vals;
                repe(v,qu) vals.push_back(arr[v]);
                sort(all(vals));
                rep(i,n/2) arr[qu[i]] = vals[i];
            }
            {
                vi vals;
                repe(v,qu) vals.push_back(brr[v]);
                sort(all(vals));
                rep(i,n/2) brr[qu[i]] = vals[i];
            }
        };
        vi q;
        rep(i,x) {
            q.push_back(i);
            q.push_back(loc[i]);
        }
        clean(q);
        q.clear();
        rep(i,n) loc[arr[i]]=i;

        repp(i,x,2*x) {
            q.push_back(i);
            q.push_back(loc[i]);
        }
        clean(q);
    };
    solve(a,b);
    solve(b,a);

    repp(i,n/2,n) cout << i+1 << ' ';
    cout << '\n';
    
    return 0;
}
