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
    int n,m;
    cin >> n >> m;
    vector<string> rows(n);
    repe(ro, rows) cin >> ro;

    int lo = 0;
    int hi = max(n,m)+1;

    vvi taken(n,vi(m));
    auto works=[&](int mid)
    {
        rep(i,n) rep(j,m) taken[i][j]=0;
        rep(i,n) rep(j,m)
        {
            if (rows[i][j]=='.') continue;
            if (taken[i][j]) continue;

            repp(a, i, i+mid)
            {
                repp(b, j, j+mid)
                {
                    if (a>=n||b>=m)
                    {
                        return false;
                    }
                    if (rows[a][b]=='.') return false;
                    if (taken[a][b])
                    {
                        return false;
                    }
                    taken[a][b]=1;
                }
            }
        }
        return true;
    };

    vi widths;
    vi heights;
    rep(i,n) rep(j,m)
    {
        if (rows[i][j]=='.') continue;
        if (!(j==0 || rows[i][j-1]=='.')) continue;
        int k =j+1;
        while (k<m&& rows[i][k]=='#') k++;
        widths.push_back(k-j);
    }
    
    rep(i,n) rep(j,m)
    {
        if (rows[i][j]=='.') continue;
        if (!(i==0 || rows[i-1][j]=='.')) continue;
        int k =i+1;
        while (k<n&& rows[k][j]=='#') k++;
        heights.push_back(k-i);
    }
    int g = widths[0];
    repe(w,widths) g=gcd(g,w);
    repe(w,heights) g=gcd(g,w);

    vi divs;
    repp(i,1,g+1) if (g%i==0) divs.push_back(i);
    reverse(all(divs));

    repe(d,divs)
    {
        if (works(d))
        {
            cout << d << '\n';
            return 0;
        }
    }

    cout << lo << '\n';

    return 0;
}

