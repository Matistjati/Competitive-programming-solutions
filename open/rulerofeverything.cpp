#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
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


signed main()
{
    fast();

    auto start = chrono::high_resolution_clock::now();
#if _LOCAL
    //ifstream in("e:/in.txt");
    //cin.rdbuf(in.rdbuf());
#endif

    int n, q;
    cin >> n >> q;

    vi ones;

    vector<p2> vids;
    rep(i, n)
    {
        int a, b;
        cin >> a >> b;
        if (a == 1) ones.push_back(b);
        else vids.emplace_back(a, b);
    }
    sort(all(ones));
    reverse(all(ones));
    sort(all(vids), [](p2 a, p2 b)
        {
            return (a.second) * (b.first - 1) > b.second * (a.first - 1);
        });

    int maxt = int(8e9) + 10;
    int p = 1;
    repe(v, vids)
    {
        p *= v.first;
        if (p > maxt) break;
    }
    if (p > maxt)
    {
        // ans is small

        vi dp(40, 0);

        rep(i, sz(ones))
        {
            for (int j = 39; j > 0; j--)
            {
                dp[j] = max(dp[j], dp[j - 1] + ones[i]);
            }
            rep(j, 40) dp[j] = min(dp[j], maxt);
        }
        rep(i, sz(vids))
        {
            for (int j = 39; j > 0; j--)
            {
                dp[j] = max(dp[j], dp[j - 1] * vids[i].first + vids[i].second);
            }
            rep(j, 40) dp[j] = min(dp[j], maxt);
        }


        while (q--)
        {
            int t;
            cin >> t;
            int ans = inf;

            rep(j, 40)
            {
                if (dp[j] >= t)
                {
                    ans = min(ans, j);
                }
            }

            if (ans == inf) ans = -1;
            cout << ans << ' ';
        }
        cout << '\n';
    }
    else
    {
        vi dp(40);
        vvi precomp(sz(ones)+1);
        auto tryv = [&](int start)
            {
                rep(i, 40) dp[i] = 0;
                dp[0] = start;

                rep(i, sz(vids))
                {
                    for (int j = 39; j > 0; j--)
                    {
                        dp[j] = max(dp[j], dp[j - 1] * vids[i].first + vids[i].second);
                    }
                    rep(j, 39) dp[j] = min(dp[j], maxt);
                }
                return dp;
            };

        precomp[0] = tryv(0);
        int s = 0;
        rep(i, sz(ones))
        {
            s += ones[i];
            precomp[i+1] = tryv(s);
        }
        vi bestcol(sz(ones)+1);
        rep(i,sz(bestcol)) bestcol[i] = *max_element(all(precomp[i]));

        auto getvpref = [&](int ind, int k)
            {
                rep(j, 40)
                {
                    if (precomp[ind][j] >= k) return j;
                }
                return inf;
            };

        stringstream out;
        while (q--)
        {
            int k;
            cin >> k;
            int lo = -1;
            int hi = sz(ones) + 1;
            while (lo + 1 < hi)
            {
                int mid = (lo + hi) / 2;
                if (bestcol[mid] >= k)
                {
                    hi = mid;
                }
                else lo = mid;
            }

            if (hi == sz(ones) + 1)
            {
                out << "-1 ";
                continue;
            }
            else
            {
                int ans = hi + getvpref(hi, k);
                repp(i, hi + 1, sz(ones) + 1)
                {
                    if (i >= ans) break;
                    ans = min(ans, i + getvpref(i, k));
                }
                out << ans << " ";
            }
        }
        cerr << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << "ms\n";
        cout << out.str();
        cout << '\n';
    }

    return 0;
}
