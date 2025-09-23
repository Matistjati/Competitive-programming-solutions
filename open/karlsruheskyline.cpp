using namespace std;
#include <bits/stdc++.h>
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;

#define rep(i,n) for (int i = 0; i < (n); i++)
#define repe(i,a) for (auto& i : a)
#define all(x) begin(x),end(x)
#define sz(x) ((int)x.size())

int main()
{
    int n,l,r;
    cin >> n >> l >> r;
    auto die = []()
    {
        cout << "no\n";
        exit(0);
    };
    if (l==1&&r==1)
    {
        die();
    }

    bool swapped=false;
    if (r==1) 
    {
        swap(l,r);
        swapped=1;
    }

    l--; r--;

    vi nums(n-1);
    rep(i,n-1) nums[i]=i+1;

    vi ans(n,-1);
    
    vi daslice;
    rep(i,l)
    {
        if (nums.empty()) die();
        daslice.push_back(nums.back());
        nums.pop_back();
    }
    reverse(all(daslice));

    rep(i,l)
    {
        ans[i]=daslice[i];
    }
    if (sz(nums)-r <0) die();
    rep(i,r)
    {
        ans[n-1-i]=nums[sz(nums)-r+i];
    }
    rep(i,r) nums.pop_back();
    nums.push_back(n);
    rep(i,n)
    {
        if (ans[i]==-1)
        {
            ans[i]=nums.back();
            nums.pop_back();
        }
    }
    if (swapped) reverse(all(ans));
    cout << "yes\n";
    repe(v,ans) cout << v << " ";

    return 0;
}

