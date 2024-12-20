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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#define clz(x) _lzcnt_u32(x)
#else
#define clz(x) __builtin_clz(x)
#endif

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            repp(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vi contestant(n);
    rep(i, n) cin >> contestant[i];
    vi problem(m);
    rep(i, m) cin >> problem[i];
    int myrating = contestant[0];
    contestant.erase(contestant.begin());
    vi c;
    repe(u, contestant) if (u > myrating) c.push_back(u);
    contestant = c;
    sort(all(contestant));
    n = sz(contestant);

    rep(i, m) if (problem[i] <= myrating) problem[i] = inf;
    sort(all(problem));
    reverse(all(problem));

    vi prefmax(m);
    prefmax[0] = problem[0];
    repp(i, 1, m) prefmax[i] = max(problem[i], prefmax[i - 1]);

    RMQ rmq(problem);


    repp(k, 1, m + 1)
    {
        int taken = 0;
        int numcontests = m / k;
        int ans = 0;

        int i;
        for (i = 0; i + k - 1 < m; i += k)
        {
            int v = rmq.query(i, i + k);
            ans += 1 + (end(contestant) - lower_bound(all(contestant), v));
        }


        cout << ans << " ";
    }
    cout << "\n";

}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
