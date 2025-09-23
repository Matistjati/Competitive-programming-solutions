using namespace std;
#include <bits/stdc++.h>


using ll = long long;

using vi = vector<ll>;

#define rep(i,b) for (int i = 0; i < (b); i++)
#define repp(i,a,b) for (int i = (a); i < (b); i++)
#define all(x) begin(x),end(x)

int main() {
    ll n,h;
    cin >> n >> h;

    ll tot_w = 0 ;
    rep(i,n)
    {
        ll a,b,c;
        cin >> a >> b >> c;
        vi nums = {a,b,c};
        sort(all(nums));
        if (*min_element(all(nums)) > h)
        {
            cout << "impossible\n";
            return 0;
        }
        auto it = upper_bound(all(nums), h);
        assert(it!=begin(nums));
        nums.erase(prev(it));
        tot_w += *min_element(all(nums));
    }
    cout << tot_w << '\n';

    return 0;

}
