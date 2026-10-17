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
    
    const int MAX = 1e7+1;
    vi is_palindrome(MAX);
    rep(i,MAX) {
        string s = to_string(i);
        string srev = s;
        reverse(all(srev));
        if (s==srev) {
            is_palindrome[i]=1;
        }
    }
    partial_sum(all(is_palindrome), begin(is_palindrome));
    auto rsq = [&](int l, int r) {
        return is_palindrome[r]-is_palindrome[l-1];
    };

    int t;
    cin >> t;
    while (t--) {
        int a,b;
        cin >> a >> b;
        cout << rsq(a,b) << '\n';
    }
    
    return 0;
}
