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

#include <sys/stat.h>
#include <unistd.h>
int main() {

    struct stat st;
    fstat(0, &st);
    string konami(st.st_size, '\0');
    read(0, &konami[0], st.st_size);

    array<int,9> dp;
    fill(all(dp),-1e9);

    int ans = 1e9;
    #pragma GCC unroll 8
    rep(i,sz(konami)) {
        char c = konami[i];
        switch (c) {
            case 'U':
                dp[1] = dp[0];
                dp[0] = i;
                break;
            case 'N':
                dp[3]=dp[2];
                dp[2]=dp[1];
                break;
            case 'V':
                dp[4]=dp[3];
                dp[6]=dp[5];
                break;
            case 'H':
                dp[5]=dp[4];
                dp[7]=dp[6];
                break;
            case 'B':
                dp[8]=dp[7];
                break;
            case 'A':
                ans = min<int>(ans, i-dp[8]);
                break;
        }
    }
    cout << ans-9 << '\n';

    return 0;
}
