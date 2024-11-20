
using namespace std;
#include <bits/stdc++.h>


#define rep(i,a,b) for(int i = a; i < b; i++)
typedef long long ll;

#define int ll

int n,k;

bitset<2501> dp[41][41][21*21];

signed main()
{
    int n,k;
    cin >> n >> k;


    dp[0][0][0] = 1;
    string s;
    cin >> s;


    rep(iter,0, s.size())
    {
        char c = s[iter];
        if (c!='?')
        {
            if (c=='N')
            {
                for (int i = 40; i > 0; i--)
                {
                    rep(j,0,21*21)
                    {
                        dp[iter+1][i][j] = dp[iter][i-1][j];
                    }
                }
            }
            else if (c=='A')
            {
                rep(i,0,41)
                {
                    for (int j = 21*21-1; j>=0; j--)
                    {
                        if (j<i) break;
                        dp[iter+1][i][j] = dp[iter][i][j-i];
                    }
                }
            }
            else if (c=='C')
            {
                rep(i,0,41) rep(j,0,21*21) dp[iter+1][i][j] = dp[iter][i][j]<<j;
            }
            else
            {
                rep(i,0,41) rep(j,0,21*21) dp[iter+1][i][j] = dp[iter][i][j];
            }
        }
        else
        {
            for (int i = 40; i > 0; i--)
            {
                rep(j,0,21*21)
                {
                    dp[iter+1][i][j] |= dp[iter][i-1][j];
                }
            }

            rep(i,0,41)
            {
                for (int j = 21*21-1; j>=0; j--)
                {
                    if (j<i) break;
                    dp[iter+1][i][j] |= dp[iter][i][j-i];
                }
            }

            rep(i,0,41) rep(j,0,21*21) dp[iter+1][i][j] |= dp[iter][i][j]<<j;

            rep(i,0,41) rep(j,0,21*21) dp[iter+1][i][j] |= dp[iter][i][j];
        }
    }

    bool good = 0;

    tuple<int,int,int,int> state;
    rep(i,0,41) rep(j,0,21*21) if (dp[n][i][j][k]) good=1, state = {n,i,j,k};
    if (good)
    {
        string ans;
        while (state != make_tuple(0,0,0,0))
        {
            int iter, i,j,t;
            tie(iter,i,j,t) = state;
            char c = s[iter-1];
            if (c!='?')
            {
                ans += c;
                iter--;
                if (c=='N')
                {
                    i--;
                }
                else if (c=='A')
                {
                    j -= i;
                }
                else if (c=='C')
                {
                    t -= j;
                }
            }
            else
            {
                if (dp[iter-1][i][j][t])
                {
                    ans += "B";
                }
                else if (i > 0 && dp[iter-1][i-1][j][t])
                {
                    ans += string(1, 'N');
                    i--;
                }
                else if (j >= i && dp[iter-1][i][j-i][t])
                {
                    ans += string(1, 'A');
                    j-=i;
                }
                else if (t >= j && dp[iter-1][i][j][t-j])
                {
                    ans += string(1, 'C');
                    t -= j;
                }
                iter--;
            }
            state = {iter,i,j,t};
        }
        reverse(ans.begin(), ans.end());
        cout << ans;
    }
    else
    {
        cout << -1;
    }
}

