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

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vi nums(n);
        rep(i, n) cin >> nums[i];

        vector<map<int, int>> num_free(2);

        rep(rem, 2)
        {
            map<int, int> cnt;
            rep(i, n)
            {
                if (i % 2 != rem) continue;
                cnt[nums[i]]++;
            }
            num_free[rem] = cnt;
        }

        vector<p2> odd_sorted;
        repe(u, num_free[1]) odd_sorted.emplace_back(u.second, u.first);
        sort(odd_sorted.rbegin(), odd_sorted.rend());
        int ans = n;
        unordered_set<int> even;
        unordered_set<int> odd;
        even.reserve(n * 2);
        odd.reserve(n * 2);

        vvi setsodd(n);
        vvi setseven(n);
        unordered_map<int, int> evenind;
        unordered_map<int, int> oddind;
        evenind.reserve(n * 2);
        oddind.reserve(n * 2);

        rep(i, n)
        {
            int a = nums[i];
            if (i % 2 == 0)
            {
                even.insert(nums[i]);
                if (evenind.find(a) == evenind.end()) evenind[a] = sz(evenind) + 1;
                setseven[evenind[a]].push_back(i);
            }
            else
            {
                odd.insert(nums[i]);
                if (oddind.find(a) == oddind.end()) oddind[a] = sz(oddind) + 1;
                setsodd[oddind[a]].push_back(i);
            }
        }

        priority_queue<tuple<int,int,int>> pq;
        repe(a,even)
        {
            if (a != odd_sorted[0].second) pq.emplace(num_free[0][a] + odd_sorted[0].first, a, 0);
            else if (sz(odd_sorted) > 1) pq.emplace(num_free[0][a] + odd_sorted[0].first, a, 1);
        }

        vector<tuple<int, int, int>> candidates;
        while (sz(candidates)<n+1&&sz(pq))
        {
            int _, a, i;
            tie(_, a, i) = pq.top();
            pq.pop();
            candidates.emplace_back(_, a, odd_sorted[i].second);
            i++;
            while (i<sz(odd_sorted)&&odd_sorted[i].second==a)
            {
                i++;
            }
            if (i<sz(odd_sorted))
            {
                pq.emplace(num_free[0][a] + odd_sorted[i].first, a, i);
            }
        }

        int times = 0;
        rep(i, sz(candidates))
        {
            times++;
            if (times > n + 1) break;
            int _, a, b;
            tie(_, a, b) = candidates[i];
            int cost = 0;
            vi* aset = &setsodd[oddind[a]];
            vi* bset = &setseven[evenind[b]];
            if (aset->size() > bset->size()) swap(aset, bset);

            int skip = -10;
            repe(u, *aset)
            {
                if (((skip+2!=u)&& binary_search(all(*bset), u - 1))|| binary_search(all(*bset), u + 1))
                {
                    cost++;
                    if (!binary_search(all(*bset), u - 1)) skip = u;
                }

            }
            ans = min(ans, n - num_free[0][a] - num_free[1][b] + cost);
        }

        cout << ans << "\n";
    }

    return 0;
}
