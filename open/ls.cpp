#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

int dp[101][101];

bool matches(int i, int j, string& pat, string& q)
{
    if (i == sz(pat) && j == sz(q)) return true;
    if (i == sz(pat)) return false;
    if (j == sz(q)) return false;

    if (dp[i][j] != -1) return dp[i][j];

    bool ret = false;
    if (pat[i] == '*')
    {
        ret |= matches(i + 1, j + 1, pat, q);
        ret |= matches(i, j + 1, pat, q);
        ret |= matches(i+1, j, pat, q);
    }
    else if (pat[i] == q[j]) ret |= matches(i + 1, j + 1, pat, q);

    return dp[i][j]=ret;
}

signed main()
{
    fast();

    string pattern;
    cin >> pattern;
    int n;
    cin >> n;

    while (n--)
    {
        memset(dp, -1, sizeof(dp));
        string file;
        cin >> file;
        if (matches(0, 0, pattern, file)) cout << file << "\n";
    }


    return 0;
}
