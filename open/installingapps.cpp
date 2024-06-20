#include <bits/stdc++.h>

using namespace std;
#define rep(i,n) for (int i = 0; i <n; i++)

int dp[510][int(2e4)];
int dpchoice[510][int(2e4)];

int best(int i, int weight, int c, vector<tuple<int,int,int,int>>& apps)
{
    if (i==apps.size())
    {
        return 0;
    }

    assert(weight<=c);
    assert(weight<=10000);
    int& v = dp[i][weight];
    if (v!=-1) return v;

    int ret = 0;
    int choice = 0;
    int __,a,b,_;
    tie(__,a,b,_)=apps[i];
    ret = max(ret, best(i+1,weight,c,apps));
    if (weight+a<=c&&weight+b<=c)
    {
        int k = 1+best(i+1,weight+b,c,apps);
        if (k>ret)
        {
            ret = k;
            choice=1;
        }
    }

    dpchoice[i][weight]=choice;
    return v=ret;
}

int main() {
    memset(dp,-1,sizeof(dp));
    memset(dpchoice,-1,sizeof(dpchoice));
    int n,c;
    cin >> n >> c;
    vector<tuple<int,int,int,int>> apps;
    rep(i,n)
    {
        int a,b;
        cin >> a >> b;
        apps.emplace_back(a-b,a,b,i);

    }
    sort(apps.rbegin(),apps.rend());
    
    best(0,0,c,apps);
    int weight = 0;

    vector<int> sol;
    rep(i,n)
    {
        assert(dpchoice[i][weight]!=-1);
        if (dpchoice[i][weight]==1)
        {
            weight+=get<2>(apps[i]);
            sol.push_back(get<3>(apps[i]));
        }
    }

    cout << sol.size() << "\n";
    rep(i,sol.size())
    {
        cout << sol[i]+1 << " ";
    }
    return 0;
}

