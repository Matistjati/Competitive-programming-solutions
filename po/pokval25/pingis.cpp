#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
#endif

vi solve(vector<p2> people)
{
    if (people.size() == 1)
    {
        if (people[0].first!=0)
        {
            cout << "-1";
            exit(0);
        }
        return { people[0].second };
    }

    vector<p2> win;
    vector<p2> lose;
    rep(i, sz(people))
    {
        p2 p = people[i];
        if (p.first > 0) win.emplace_back(p2(p.first-1,p.second));
        else lose.emplace_back(people[i].second, i);
    }

    vi sol(sz(people));
    if (sz(win) != sz(lose))
    {
        cout << "-1";
        exit(0);
    }

    sort(all(lose));
    vi winp = solve(win);
    rep(i, sz(win))
    {
        int a = winp[i];
        int b = lose[i].first;
        sol[i * 2] = min(a, b);
        sol[i * 2 + 1] = max(a, b);
    }

    return sol;
}

int main()
{
    fast();

    int n;
    cin >> n;
    vector<p2> people(n);
    rep(i, n) cin >> people[i].first, people[i].second = i;

    vi ans = solve(people);
    repe(u, ans) cout << u+1 << " ";

    return 0;
}
