#pragma GCC optimize ("Ofast")
using namespace std;
#include <bits/stdc++.h>


#define rep(i,a,b) for(int i = a; i < b; i++)
typedef long long ll;

typedef pair<int,int> p2;

signed main()
{
    int n, a, b;
    cin >> n >> a >> b;
    vector<tuple<int,int,int,int>> rect;
    rep(i,0,n)
    {
        int loa,hia,lob,hib;
        cin >> loa >> hia >> lob >> hib;
        loa = max(0, loa-a);
        hia = min(5001, hia-a);
        lob = max(0, lob-b);
        hib = min(5001, hib-b);
        rect.emplace_back(loa,hia,lob,hib);
    }

    bitset<5002> bsets[5002];
        bitset<5002> vis[5002];
    vis[0][0] = 1;
    bsets[0][0] = 1;


    int ans = 0;

    rep(rect_ind,0,n)
    {
        int loa,hia,lob,hib;
        tie(loa,hia,lob,hib) = rect[rect_ind];
        vector<p2> found;
        rep(i,loa,hia+1)
        {
            int v = lob-1;
            while (1)
            {
                v = bsets[i]._Find_next(v);
                if (v==5002 || v > hib) break;
                bsets[i][v]=0;
                found.emplace_back(i+1, v);
                found.emplace_back(i, v+1);
            }
        }
        for (auto p : found)
        {
            ans = max(ans, p.first+p.second);
            if (!vis[p.first][p.second])
            {
                vis[p.first][p.second]=1;
                bsets[p.first][p.second]=1;
            }
        }
    }
    
    cout << ans;
}

