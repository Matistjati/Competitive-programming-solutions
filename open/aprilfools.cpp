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

    string temp;
    getline(cin, temp);
    ll t = stoi(temp);
    while (t--)
    {
        getline(cin, temp);
        ll shift = stoi(temp);

        string str;
        getline(cin, str);
        repe(c, str)
        {
            if (c >= 65 && c <= 90)
            {
                ll k = c - 65;
                k -= shift;
                if (k < 0) k += (90 - 65 + 1);
                cout << ((char)(k + 65));
            }
            else
            {
                cout << c;
            }

        }
        cout << "\n";
    }

    return 0;
}
