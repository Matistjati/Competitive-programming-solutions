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

double solve(int i, vi& nums) {
    double lo = 0;
    double hi = 1;

    int s = 0;
    repe(num, nums) s += num;

    rep(_, 30)
    {
        double mid = (lo + hi) / 2;

        double totcost = 0;
        double myscore = nums[i]+s*mid;
        rep(j, nums.size())
        {
            if (i == j) continue;
            if (nums[j] > myscore)
            {
                continue;
            }
            double theirscore = nums[j];
            totcost += (myscore +0.0000001 - theirscore) / s;
        }
        if (totcost+mid>=1)
        {
            hi = mid;
        }
        else
        {
            lo = mid;
        }

    }
    return (hi+lo)/2;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
    rep(FUCKYOU, t)
    {
		int n;
		cin >> n;
		vi nums(n);
		rep(i,n) cin >> nums[i];
        cout << "Case #" << FUCKYOU+1 << ": ";
        rep(i, n)
        {
            cout << fixed << setprecision(15) << solve(i, nums) * 100 << ' ';
        }
        cout << "\n";
    }

    return 0;
}
