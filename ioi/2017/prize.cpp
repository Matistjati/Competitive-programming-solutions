#include "prize.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll linf = ll(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

map<int, vi> cache;
vi q(int i)
{
    if (cache.find(i) != cache.end()) return cache[i];
    return cache[i] = ask(i);
}

int find_best(int n)
{
    int lollipop_cnt = 0;
    int i = 0;
    while (i < 500)
    {
        vi res = q(i);
        if (res[0] + res[1] == 0)
        {
            return i;
        }
        lollipop_cnt = max(lollipop_cnt, res[0] + res[1]);
        if (lollipop_cnt > 30)
        {
            break;
        }
        i++;
    }

    int jump = 220;
    while (true)
    {
        vi base = q(i);
        if (base[0] + base[1] == 0)
        {
            return i;
        }

        if (base[0] + base[1] == lollipop_cnt)
        {
            if (i + jump < n)
            {
                vi b2 = q(i + jump);
                if (b2 == base)
                {
                    i += jump;
                    continue;
                }
            }

            int lo = i;
            int hi = min(n, i + jump);
            while (lo + 1 < hi)
            {
                int mid = (lo + hi) / 2;
                vi m = q(mid);
                if (m == base)
                {
                    lo = mid;
                }
                else hi = mid;
            }
            i = hi;
        }
        else
        {
            i++;
        }
    }

    return 0;
}
