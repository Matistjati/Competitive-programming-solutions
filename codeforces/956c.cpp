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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

void solve()
{
    int n;
    cin >> n;

    vi vala(n);
    vi valb(n);
    vi valc(n);
    rep(i, n) cin >> vala[i];
    rep(i, n) cin >> valb[i];
    rep(i, n) cin >> valc[i];
    int tot = accumulate(all(vala), 0LL);
    assert(tot==accumulate(all(valb), 0LL));
    int tot3 = (tot + 2) / 3;

    vvi arrs = { vala,valb,valc };

    vi prefa(vala);
    repp(i, 1, n) prefa[i] += prefa[i - 1];
    vi prefb(valb);
    repp(i, 1, n) prefb[i] += prefb[i - 1];
    vi prefc(valc);
    repp(i, 1, n) prefc[i] += prefc[i - 1];


    auto rsq = [](vi& pref, int l, int r)
    {
        if (l) l = pref[l - 1];
        return pref[r] - l;
    };
    vvi pref = { prefa,prefb,prefc };
    bool good = 0;

    repp(i, 1, n)
    {
        vi order = { 0,1,2 };
        do
        {
            if (rsq(pref[order[0]], 0, i - 1) < tot3) continue;
            int lo = i - 1;
            int hi = n;
            while (lo + 1 < hi)
            {
                int mid = (lo + hi) / 2;
                if (rsq(pref[order[1]], i, mid) >= tot3)
                {
                    hi = mid;
                }
                else lo = mid;
            }
            if (hi == n) continue;
            assert(rsq(pref[order[1]], i, hi) >= tot3);
            if (rsq(pref[order[2]], hi + 1, n - 1) < tot3) continue;
            vector<p2> ans(3);
            ans[order[0]] = p2(1, i);
            ans[order[1]] = p2(i+1, hi+1);
            ans[order[2]] = p2(hi+2,n);
            cout << ans[0].first << " " << ans[0].second << " " << ans[1].first << " " << ans[1].second << " " 
                << ans[2].first << " " << ans[2].second << " " << "\n";
            good = 1;
            break;
        } while (next_permutation(all(order)));
        if (good) break;
    }
    if (!good) cout << "-1\n";
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
