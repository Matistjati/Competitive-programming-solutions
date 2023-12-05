#include <bits/stdc++.h>
using namespace std;
#include <cassert>

#define rep(i,n) for (int i = 0; i < n; i++)
#define all(x) begin(x),end(x)
typedef long long ll;
typedef vector<ll> vi;



int main()
{
    int n, x, y;
    cin >> n >> x >> y;

    vi nums(n);
    rep(i, n) cin >> nums[i], nums[i] *= x;
    sort(all(nums));

    int t = 0;
    int cnt = 0;
    rep(i, n)
    {
        double newavg = (t + nums[i]) / (cnt + 1.0);
        if (newavg <= y)
        {
            t += nums[i];
            cnt++;
        }
    }

    cout << cnt;


    return 0;
}

