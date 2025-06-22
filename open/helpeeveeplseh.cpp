#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }


signed main()
{
    fast();

    string s;
    cin >> s;
    int goodpairs = 0;
    int ans = 0;
    int i = 1;
    int j = sz(s) - 1;
    vi good(sz(s));
    while (i<j)
    {
        if (s[i]==s[j])
        {
            good[i] = 1;
            good[j] = 1;
            goodpairs++;
        }
        i++; j--;
    }
    int pairgoal = (sz(s) - 1) / 2;
    ans += goodpairs == pairgoal;
    string sorig = s;
    rep(i, sz(s) - 1)
    {
        char c = sorig[i];
        int goodbefore = good[i + 1] && good[sz(s) - 1 - i];
        good[i + 1] = 0;
        good[sz(s)-1-i] = 0;
        goodpairs -= goodbefore;

        s[i + 1] = c;
        if (i+1!=sz(s)-1-i&& s[i + 1] == s[sz(s) - 1 - i])
        {
            goodpairs++;
            good[i + 1] = 1;
            good[sz(s) - 1 - i] = 1;
        }
        ans += goodpairs == pairgoal;
    }

    cout << ans;

    return 0;
}
