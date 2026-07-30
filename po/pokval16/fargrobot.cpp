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


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    string colors;
    cin >> colors;
    string ans = "";

    int index = 0;
    while (ans.size() < n)
    {
        int r = 0;
        int g = 0;
        int b = 0;
        int n_colored = 0;
        char chosen = 'S';
        for (int i = index; i < colors.size(); i++)
        {
            if (colors[i] == 'R')
            {
                if (r == 0)
                {
                    n_colored++;
                    if (n_colored > 2)
                    {
                        chosen = 'R';
                    }
                    r++;
                }
                else
                {
                    r++;
                }
            }
            if (colors[i] == 'G')
            {
                if (g == 0)
                {
                    n_colored++;
                    if (n_colored > 2)
                    {
                        chosen = 'G';
                    }
                    g++;
                }
                else
                {
                    g++;
                }
            }
            if (colors[i] == 'B')
            {
                if (b == 0)
                {
                    n_colored++;
                    if (n_colored > 2)
                    {
                        chosen = 'B';
                    }
                }
                b++;
            }
            if (chosen != 'S')
            {
                ans += chosen;
                index = i+1;
                break;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}