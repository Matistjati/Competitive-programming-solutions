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

    vi palindromes;

    auto ispalindrome = [](int x)
        {
            string s = to_string(x);
            string rev = s;
            reverse(all(rev));
            if (rev[0] == '0') return false;
            return s == rev;
        };

    repp(i, int(1e5), int(1e6)) if (ispalindrome(i)) palindromes.push_back(i);
    int n;
    cin >> n;
    while (n--)
    {
        int q;
        cin >> q;
        int best = -inf;
        repe(p, palindromes)
        {
            if (abs(p - q) < abs(q - best))
            {
                best = p;
            }
        }
        cout << best << '\n';
    }


    return 0;
}
