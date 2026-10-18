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
    
    vector<vector<int>> st(3, vector<int>(3));
    st[0][0]=1;
    rep(i,n) {
        vector<vector<int>> newst(3, vector<int>(3));
        string x;
        cin >> x;
        rep(l, 3) {
            rep(r,3) {
                if (!st[l][r]) continue;
                rep(side,2) {

                    auto apply = [&](int val) {
                        vector<int> inds = {l,r};
                        inds[side]=val;
                        newst[inds[0]][inds[1]]=1;    
                    };

                    vector<int> inds = {l,r};
                    if (x=="👟") {
                        if (inds[side]==1) {
                            apply(2);
                        }
                        if (inds[side]==2) {
                            apply(1);
                        }
                    }
                    else {
                        inds = {l,r};
                        if (inds[side]==0) {
                            apply(1);
                        }
                        inds = {l,r};
                        if (inds[side]==1) {
                            apply(0);
                        }
                    }
                }
                
            }
        }
        
        st = newst;
    }

    cout << (st[2][2] ? "gilt" : "ógilt");
    
    return 0;
}
