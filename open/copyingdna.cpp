#pragma GCC optimize("O3")
#pragma GCC target("avx2,lzcnt")
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


char dp[1<<18];
const ll smallinf = 100;
void solve() {
    string s,t;
    cin >> s >> t;
    int n = sz(s), m = sz(t);
    fill(all(dp),smallinf);

    vector<int> longest_match_s(m);
    rep(i,m) {
        rep(j,n) {
            rep(l,m) {
                if (i+l>=m||j-l<0) break;
                if (t[i+l]!=s[j-l]) break;
                longest_match_s[i] = max<int>(longest_match_s[i], l+1);
            }
            rep(l,m) {
                if (i+l>=m||j+l>=n) break;
                if (t[i+l]!=s[j+l]) break;
                longest_match_s[i] = max<int>(longest_match_s[i],l+1);
            }
        }
    }

    dp[0]=0;
    vector<vector<int>> longest_match(m, vector<int>(m)), longest_matchrev(m, vector<int>(m));
    rep(i,m) {
        rep(j,m) {
            rep(l,m) {
                if (max(i+l,j+l)>=m) break;
                if (t[i+l]!=t[j+l]) break;
                longest_match[i][j]=l+1;
            }
            rep(l,m) {
                if (i+l>=m || j-l < 0) break;
                if (t[i+l]!=t[j-l]) break;
                longest_matchrev[i][j]=l+1;
            }
        }
    }
    vector<int> longest_match2(m), nzerof(m), nzeror(m);
    auto ctz = [](int x) {
        return countr_zero((unsigned)x);
    };
    auto clz = [](int x) {
        return countl_zero((unsigned)x);
    };
    rep(mask, 1<<m) {
        if (dp[mask]==smallinf) continue;

        rep(i,m) nzerof[i] = ctz(~mask >> i);
        rep(i,m) nzeror[i] = clz(~(mask << (31-i)));
        rep(i,m) {
            int v = longest_match_s[i];
            rep(j,m) {
                v = max(v, min({longest_match[i][j], nzerof[j]}));
                v = max(v, min({longest_matchrev[i][j], nzeror[j]}));
            }
            longest_match2[i] = v;
        }

        rep(i,m) {
            int new_mask = mask;
            repp(j,i,min<int>(m,i+longest_match2[i])) {
                if (mask&(1<<j)) break;
                new_mask |= (1<<j);
                dp[new_mask] = min<char>(dp[new_mask], dp[mask]+1);
            }
        }
    }

    if (dp[(1<<m)-1]==smallinf) cout << "impossible\n";
    else cout << (int)dp[(1<<m)-1] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
