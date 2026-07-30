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

    int n, k;
    cin >> n >> k;

    vector<string> input_col;
    vector<pair<int,int>> colors;
    int m = 0;
    rep(i, k)
    {
        string color;
        int cnt;
        cin >> color >> cnt;
        m = max(m, cnt);
        input_col.push_back(color);
        colors.emplace_back(cnt, i);
    }

    if (m * 2 >= n + 1)
    {
        cout << "Nej\n";
        return 0;
    }
    sort(colors.rbegin(), colors.rend());

    vector<int> ans(n, -1);

    // Greedily place colors. Take largest colors first, and place them
    // round-robin style in first available slot
    // Amortizes to O(n)
    int j = 0;
    for (auto [cnt, col] : colors)
    {
        rep(i, cnt)
        {
            while (ans[j] != -1)
            {
                j = (j + 1) % n;
            }
            ans[j] = col;
            j = (j + 2) % n;
        }
    }

    cout << "Ja\n";
    repe(c, ans) cout << input_col[c] << ' ';

    return 0;
}
