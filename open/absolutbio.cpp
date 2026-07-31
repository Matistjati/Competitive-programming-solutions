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

bitset<int(1e9)+10> seen;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,q;
    cin >> n >> q;

    while(q--) {
        int a,b;
        cin >> a >> b;
        if (a==1) {
            if (seen[b]) {
                cout << "Upptagen\n";
            }
            else {
                cout << "Ledig\n";
                seen[b]=1;
            }
        }
        else {
            int c;
            cin >> c;
            if (seen[c]) {
                cout << "Upptagen\n";
            }
            else {
                cout << "Ledig\n";
                seen[b]=0;
                seen[c]=1;
            }
        }
    }

    return 0;
}
