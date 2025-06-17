#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

vector<string> split(string s, string d) { size_t k = 0, n, e = d.length(); string t; vector<string> r; while ((n = s.find(d, k)) != string::npos) { t = s.substr(k, n - k); k = n + e; r.push_back(t); } r.push_back(s.substr(k)); return r; }

p2 merge_side(p2 a, p2 b)
{
    return p2(max(a.first, b.first), a.second + b.second);
}

p2 merge_other(p2 a, p2 b)
{
    return p2(a.first + b.first, max(a.second, b.second));
}


int minarea(p2 a, p2 b, p2 c)
{
    vector<p2> rects = { a,b,c };
    sort(all(rects));
    int ans = int(5e18);

    do
    {

        rep(i, 2)
        {
            rep(j, 2)
            {
                p2 asd;
                if (i) asd = merge_side(rects[0], rects[1]);
                else asd = merge_other(rects[0], rects[1]);
                if (j) asd = merge_side(asd, rects[2]);
                else asd = merge_other(asd, rects[2]);
                ans = min(ans, asd.first * asd.second);
            }
        }

    } while (next_permutation(all(rects)));
    return ans;
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        p2 a, b, c;
        cin >> a.first >> a.second;
        cin >> b.first >> b.second;
        cin >> c.first >> c.second;

        int ans = int(5e18);
        rep(i, 2)
        {
            rep(j, 2)
            {
                rep(k, 2)
                {
                    p2 aa = a;
                    p2 bb = b;
                    p2 cc = c;
                    if (i) swap(aa.first, aa.second);
                    if (j) swap(bb.first, bb.second);
                    if (k) swap(cc.first, cc.second);
                    ans = min(ans, minarea(aa, bb, cc));
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
