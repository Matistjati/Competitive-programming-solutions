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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    string s;
    cin >> s;

    set<string> words;
    repp(i, 1, sz(s))
    {
        string a = s.substr(0, i);
        string b = s.substr(i);
        repp(j, 1, sz(b))
        {
            string cc = b.substr(j);
            string bb = b.substr(0, j);
            string aa = a;
            reverse(all(aa));
            reverse(all(bb));
            reverse(all(cc));
            words.insert(aa + bb + cc);
        }
    }


    cout << *begin(words);

    return 0;
}
