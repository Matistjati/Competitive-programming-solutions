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
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int n;
    cin >> n;
    set<string> good;
    rep(i, n)
    {
        string v;
        cin >> v;
        std::transform(v.begin(), v.end(), v.begin(),
            [](unsigned char c) { return std::tolower(c); });
        good.insert(v);
    }

    bool isgood = 1;
    string x;
    while (cin >> x)
    {
        std::transform(x.begin(), x.end(), x.begin(),
            [](unsigned char c) { return std::tolower(c); });
        if (good.find(x) == good.end())
        {
            isgood = 0;
        }
    }
    if (isgood) cout << "Hi, how do I look today?";
    else cout << "Thore has left the chat";

    return 0;
}
