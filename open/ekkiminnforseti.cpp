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
#endif


int32_t main()
{
    fast();

    int n, m;
    cin >> n >> m;

    vector<string> names;

    vvi votes(n, vi(m));

    rep(i, m)
    {
        string x;
        cin >> x;
        names.push_back(x);
    }

    rep(i, n) rep(j, m) cin >> votes[i][j], votes[i][j]--;

    vi ptr(n);
    vi lost(m);
    vvi voters(m);
    rep(i, n) voters[votes[i][0]].push_back(i);
    vi votecnt(m);

    rep(i, n)
    {
        while (lost[votes[i][ptr[i]]])
        {
            ptr[i]++;
        }
        votecnt[votes[i][ptr[i]]]++;
    }
    set<p2> minq;
    set<p2> maxq;
    rep(i, m)
    {
        int v = votecnt[i];
        minq.insert(p2(v, -i));
        maxq.insert(p2(-v, i));
    }
    while (true)
    {
        
        if (-begin(maxq)->first * 2 > n)
        {
            cout << names[begin(maxq)->second];
            return 0;
        }
        while (lost[-begin(minq)->second])
        {
            minq.erase(minq.begin());
        }
        int least = -begin(minq)->second;
        minq.erase(minq.begin());

        lost[least] = 1;
        repe(i, voters[least])
        {
            while (lost[votes[i][ptr[i]]])
            {
                ptr[i]++;
            }
            int w = votes[i][ptr[i]];
            int& v = votecnt[votes[i][ptr[i]]];

            maxq.erase(p2(-v, w));
            minq.erase(p2(v, -w));
            v++;
            minq.insert(p2(v, -w));
            maxq.insert(p2(-v, w));
            voters[w].push_back(i);
        }
    }


    return 0;
}
