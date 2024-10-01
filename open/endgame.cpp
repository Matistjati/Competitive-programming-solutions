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

int n;
vector<p2> delta;
bool two_moves_possible(p2 a, p2 b)
{
    set<p2> from_a;
    rep(i, sz(delta))
    {
        p2 np = p2(a.first + delta[i].first, a.second + delta[i].second);
        if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= n) continue;
        from_a.insert(np);
    }


    rep(i, sz(delta))
    {
        p2 np = p2(b.first - delta[i].first, b.second - delta[i].second);
        if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= n) continue;
        if (from_a.count(np)) return 1;
    }

    return 0;
}



signed main()
{
    fast();

    cin >> n;
    p2 p1, p_2;
    cin >> p1.first >> p1.second >> p_2.first >> p_2.second;
    p1.first--;
    p1.second--;
    p_2.first--;
    p_2.second--;
    delta.resize(n);
    rep(i, n) cin >> delta[i].first >> delta[i].second;
    delta.emplace_back(p2(0, 0));
    if (two_moves_possible(p1, p_2))
    {
        cout << "Alice wins";
        return 0;
    }

    uniform_int_distribution<int> dist(0, n - 1);
    random_device rd;
    mt19937 rng(rd());
    rep(i, 30)
    {
        p2 p = p2(dist(rng), dist(rng));
        if (!two_moves_possible(p_2,p))
        {
            cout << "tie " << p.first + 1 << " " << p.second + 1;
            return 0;
        }
    }

    cout << "Bob wins";

    return 0;
}
