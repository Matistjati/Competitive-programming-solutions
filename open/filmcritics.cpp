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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

#define gc() getchar_unlocked()
inline void read(int& v) { v = 0; char c;  while ((c = gc()) && c != ' ' && c != '\n') { if (c == EOF) { v = -1; return; } v *= 10; v += c - '0'; } }


signed main()
{
    fast();

    int n, m, k;
    read(n);
    read(m);
    read(k);
    if (k % m != 0)
    {
        cout << "impossible";
        return 0;
    }
    int num_yes = k / m;

    vi ratings(n);
    rep(i, n)
    {
        read(ratings[i]);
    }
    vector<p2> people(n);
    rep(i, n) people[i] = p2(ratings[i], i);
    sort(all(people));
    vi yes_sayers;
    vi no_sayers;
    rep(i, n - num_yes) no_sayers.push_back(people[i].second);
    repp(i, n - num_yes, n) yes_sayers.push_back(people[i].second);
    reverse(all(no_sayers));

    auto die = []()
    {
        cout << "impossible";
        exit(0);
    };


    vi ans;
    int yes = 0;
    int no_i = 0;
    int yes_i = 0;
    rep(i, n)
    {
        if (yes_i < sz(yes_sayers) && yes_i * m <= ratings[yes_sayers[yes_i]] * i)
        {
            ans.push_back(yes_sayers[yes_i]);
            yes_i++;
        }
        else if (no_i < sz(no_sayers) && yes_i * m > ratings[no_sayers[no_i]] * i)
        {
            ans.push_back(no_sayers[no_i]);
            no_i++;
        }
        else die();
    }

    repe(u, ans) cout << u + 1 << "\n";

    return 0;
}
