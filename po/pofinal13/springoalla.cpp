#include <bits/stdc++.h>
using namespace std;

//typedef long long ll;
//#define int ll
const int inf = int(1e9);

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


signed main()
{
    fast();

    int n, t;
    cin >> n >> t;
    
    vi trails(n);

    rep(i, n)
    {
        int tlen;
        cin >> tlen;
        trails[i] = tlen;
    }

    // sorting makes the memory accesses slightly more structured
    vi trailsc(trails);
    sort(all(trailsc));

    vi memo(t+1, inf);
    memo[0] = 0;
    
    repe(tlen, trailsc)
    {
        repp(i, tlen, memo.size())
        {
            memo[i] = min(memo[i], memo[i - tlen] + 1);
        }
    }
    repe(tlen, trailsc)
    {
        int twice_time = tlen + tlen / 2;
        repp(i, twice_time, memo.size())
        {
            memo[i] = min(memo[i], memo[i - twice_time] + 2);
        }
    }
    
    p2 best = p2(inf, inf);
    rep(time, sz(memo))
    {
        if (memo[time] == inf) continue;
        // time + x >= t
        // x >= t-time
        auto it = lower_bound(all(trailsc), t - time);
        if (it != trailsc.end()) best = min(best, p2(time + *it, memo[time] + 1));
    }
    
    rep(time, sz(memo))
    {
        if (memo[time] == inf) continue;
        // time + x*1.5 >= t
        // x >= (t-time)/1.5
        // x >= 2*(t-time)/3
        auto it = lower_bound(all(trailsc), (2*(t - time)+2)/3);
        if (it != trailsc.end()) best = min(best, p2(time + (*it+*it/2), memo[time] + 2));
    }
    
    int time = best.first;
    int numruns = best.second;
    cout << time << " " << numruns << "\n";

    vi runs(n);
    while (time > 0)
    {
        rep(j, n)
        {
            int tlen = trails[j];
            if (time - tlen >= 0 && memo[time - tlen] == numruns -1)
            {
                runs[j] += tlen;
                time -= tlen;
                numruns--;
            }
            int twice_time = tlen + tlen / 2;
            if (time - twice_time >= 0 && memo[time - twice_time] == numruns - 2)
            {
                runs[j] += twice_time;
                time -= twice_time;
                numruns -= 2;
            }
        }
    }
    repe(u, runs) cout << u << " ";

    return 0;
}
