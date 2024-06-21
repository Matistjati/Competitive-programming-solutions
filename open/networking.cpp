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


int dp[1001][int(1e4 + 10)];
int best(int i, int c, int k, vvi& choices)
{
    if (c > k)
    {
        return 0;
    }
    if (i == choices.size())
    {
        return c;
    }
    int& v = dp[i][c];
    if (v != -1) return v;

    int ret = max(0LL, best(i + 1, c, k, choices));

    repe(u, choices[i]) ret = max(ret, best(i + 1, c + u, k, choices));

    return v = ret;
}

signed main()
{
    fast();

    memset(dp, -1, sizeof(dp));
    int n, k;
    cin >> n >> k;

    map<string, vi> lect;
    rep(i, n)
    {
        int v;
        string name;
        cin >> v >> name;
        lect[name].push_back(v);
    }
    vvi choices;
    repe(v, lect) choices.push_back(v.second);
    cout << best(0, 0, k, choices);
    return 0;
}
