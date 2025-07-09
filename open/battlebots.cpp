#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

#define rep(i, b) for(int i = 0; i < (b); i++)
#define repp(i, a, b) for(int i = a; i < (b); i++)
#define repe(i,arr) for (auto& i : arr)
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
typedef pair<int, int> p2;
typedef vector<int> vi;
typedef vector<vi> vvi;


signed main()
{
    cin.tie(0)->sync_with_stdio(0);

    int x;
    cin >> x;
    if (x==1)
    {
        cout << "1";
        return 0;
    }
    int ans = 0;
    int rem = 0;
    while (x>1)
    {
        rem += x % 2;
        x /= 2;
        ans++;
    }
    if (x == 1 && rem) ans += 2;
    else if (x==1) ans++;
    cout << ans;

    return 0;
}

