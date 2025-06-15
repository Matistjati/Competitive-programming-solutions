#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

string scs(string& a, string& b, const string& lcs)
{
    string ans;
    int i = 0, j = 0;
    for (char c : lcs)
    {
        while (i < sz(a) && a[i] != c) ans += a[i++];
        while (j < sz(b) && b[j] != c) ans += b[j++];
        ans += c;
        i++,j++;
    }
    while (i < sz(a)) ans += a[i++];
    while (j < sz(b)) ans += b[j++];
    return ans;
}


signed main()
{
    string a, b, lcs;
    cin >> a >> b >> lcs;

    cout << scs(a, b, lcs) << '\n';
}
