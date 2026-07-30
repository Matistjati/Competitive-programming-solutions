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

const int MAX_N = 1000;
using bset = bitset<MAX_N>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    int largest_bit = 0;
    rep(i, 20) if ((n - 1) & (1 << i)) largest_bit = i;

    vector<bset> resp, asks;
    rep(bit, largest_bit + 1) {
        bset use;
        rep(i, n) {
            if (i & (1 << bit)) use[i] = 1;
        }

        asks.push_back(use);
        int num_ask = use.count();
        if (num_ask) {
            cout << "ASK " << num_ask << ' ';
            rep(i, n) if (use[i]) cout << i + 1 << ' ';
            cout << endl;
        }
        

        bset res;
        rep(i, num_ask) {
            int x;
            cin >> x;
            res[x - 1] = 1;
        }
        resp.push_back(res);
    }

    cout << "ANSWER ";
    rep(i, n) {
        int ind=0;
        rep(bit, largest_bit + 1) {
            if (resp[bit][i]) ind |= (1<<bit);
        }
        cout << ind+1 << ' ';
    }
    cout << endl;


    return 0;
}
