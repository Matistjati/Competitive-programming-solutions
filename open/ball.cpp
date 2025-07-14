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

    int n;
    cin >> n;
    map<p2, int> ps;
    vi deg(n);
    rep(i, n/2+1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        deg[a]++;
        deg[b]++;
    }
    rep(i, n) if (deg[i] == 2) cout << i + 1 << " ";


    return 0;
}

