#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(ind, hi) for(int ind = 0;ind<hi;ind++)

ll mod = ll(1e9 + 7);

ll dp[5][int(1e6 + 10)];
ll cnt(int i, int color, vector<ll>& nums)
{
    if (color == 3) return 1LL;
    if (i == nums.size()) return 0;

    ll& v = dp[color][i];
    if (v != -1) return v;

    ll ret = 0LL;

    //cout << i << " " << color << "\n";
    if (color == 0)
    {
        if (nums[i] == 1) ret = (ret + cnt(i + 1, color + 1, nums)) % mod;
        ret = (ret + cnt(i + 1, color, nums)) % mod;

    }
    else if (color == 1)
    {
        if (nums[i] == 2) ret = (ret + cnt(i + 1, color + 1, nums)) % mod;
        ret = (ret + cnt(i + 1, color, nums)) % mod;
    }
    else if (color == 2)
    {
        if (nums[i] == 2) ret = (ret + cnt(i + 1, color, nums)) % mod;
        else if (nums[i] == 3) ret = (ret + cnt(i + 1, color + 1, nums)) % mod;
        ret = (ret + cnt(i + 1, color, nums)) % mod;
    }

    return v = ret;
}

int main()
{
    ll n;
    cin >> n;
    vector<ll> nums(n);
    rep(i, n) cin >> nums[i];
    memset(dp, -1, sizeof(dp));
    cout << cnt(0, 0, nums);
}
