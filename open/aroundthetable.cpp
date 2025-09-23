using namespace std;
#include <bits/stdc++.h>
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;

#define rep(i,n) for (int i = 0; i < (n); i++)
#define repp(i,a,b) for (int i = (a); i < (b); i++)
#define repe(i,a) for (auto& i : a)
#define all(x) begin(x),end(x)
#define sz(x) ((int)x.size())

int main()
{
    auto simulate_fast = [](ll l, ll r)
    {
        if (r+1==l) return 2*l-1;
        if ((l+r)%2==1) return 2*(l+r);
        if (l==r) return 3*l;
        if (r+2==l) return 3*l-3;
        return 2*(r+l);
    };

    int a,b;
    cin >> a >> b;
    cout << simulate_fast(a,b) << '\n';
    return 0;

}

