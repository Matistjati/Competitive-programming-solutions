#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i = 0; i < n; i++)
typedef vector<int> vi;


int main()
{
    int n;
    cin >> n;
    vi nums(n);
    rep(i,n)cin>>nums[i];

    bool sorted = 1;
    for (int i = 0; i < n-1; i++) sorted&=nums[i]<=nums[i+1];
    if (sorted)
    {
        cout << "1 1";
        return 0;
    }

    vi unique;
    vi mapping;
    int prevv =-1;
    rep(i,n)
    {
        if (nums[i]==prevv)
        {
            continue;
        }
        unique.push_back(nums[i]);
        mapping.push_back(i);
        prevv = nums[i];
    }


    int on = 0;
    int lo = -1;
    int hi = -1;
    rep(i,unique.size()-1)
    {
        if (on==0 && unique[i]>unique[i+1])
        {
            on=1;
            lo = mapping[i];

        }
        else if (on==1&&!(unique[i]>unique[i+1]))
        {
            on=2;
            hi = mapping[i];
        }
    }

    if (on==1)
    {
        reverse(nums.begin()+lo, nums.end());

        bool works = 1;
        rep(i,n-1) works&=nums[i]<=nums[i+1];
        if (works)
        {
            cout << lo+1 << " " << n;
            return 0;
        }
        else
        {
            cout << "impossible";

        }
    }
    else
    {
        while (hi+1<n&&nums[hi]==nums[hi+1])hi++;
        reverse(nums.begin()+lo, nums.begin()+hi+1);
        bool works = 1;
        rep(i,n-1) works&=nums[i]<=nums[i+1];
        if (works)
        {
            cout << lo+1 << " " << hi+1;
            return 0;
        }
        else
        {
            cout << "impossible";

        }
    }

    return 0;
}
