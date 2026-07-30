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

    int pa, ka, pb, kb, n;
    cin >> pa >> ka >> pb >> kb >> n;

    int minV = 1e9;
    int a = 0;
    int b = 0;
    rep(i, 100)
    {
        rep(j, 100)
        {
            if (i*ka+j*kb >= n)
            {
                ll cost = i * pa + j * pb;
                if (cost < minV)
                {
                    minV = i * pa + j * pb;
                    a = i;
                    b = j;
                }
            }
        }
    }
    cout << a << " " << b << " " << minV << '\n';

    return 0;
}
