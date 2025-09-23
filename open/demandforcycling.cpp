using namespace std;
#include <bits/stdc++.h>
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (int i = 0; i < (n); i++)
#define repp(i,a,b) for (int i = (a); i < (b); i++)
#define repe(i,a) for (auto& i : a)
#define all(x) begin(x),end(x)
#define sz(x) ((int)x.size())

int main()
{
    int n;
    cin >> n;
    p2 ma = p2(0, 0);
    p2 mi = p2(inf, inf);

    rep(i, n)
    {
        ll a, b;
        cin >> a >> b;
        ma.first = max(ma.first, a);
        ma.second = max(ma.second, b);
        mi.first = min(mi.first, a);
        mi.second = min(mi.second, b);
    }
    cout << "4\n";
    cout << ma.first << " " << ma.second << '\n';
    cout << mi.first << " " << ma.second << '\n';
    cout << mi.first << " " << mi.second << '\n';
    cout << ma.first << " " << mi.second << '\n';

    return 0;
}

