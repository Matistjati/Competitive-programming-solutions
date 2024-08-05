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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
constexpr const int maxv = int(2e4);
const int padded_size = maxv + 64 - maxv % 64;
constexpr const int num_chunks = int(padded_size / 64);
constexpr const int mask_64 = 63;


typedef unsigned long long ull;
struct custom_bitset
{
    vector<ull> chunks;

    custom_bitset() : chunks(num_chunks)
    {
        assert(padded_size % 64 == 0);
        assert(sizeof(ull) == 8);
    }

    void enable(int ind)
    {
        assert((ind >> 6) == ind / 64);
        int outer_index = ind >> 6;
        int inner_index = ind & mask_64;
        chunks[outer_index] |= (1ull << inner_index);
    }
    void disable(int ind)
    {
        assert((ind >> 6) == ind / 64);
        int outer_index = ind >> 6;
        int inner_index = ind & mask_64;
        chunks[outer_index] &= ~(1ull << inner_index);
    }
    bool get(int ind)
    {
        assert((ind >> 6) == ind / 64);
        int outer_index = ind >> 6;
        int inner_index = ind & mask_64;
        return (chunks[outer_index] & (1ull << inner_index)) > 0;
    }
    void shift_or(ull offset)
    {
        int offset_outer = offset / 64;
        int offset_inner = offset % 64;
        bool zero_mod = offset_inner == 0;
        if (zero_mod)
        {
            for (int chunk = num_chunks - 1; chunk >= (int)offset / 64; chunk--)
            {
                chunks[chunk] |= chunks[chunk - offset_outer] << offset_inner;
            }
        }
        else
        {
            for (int chunk = num_chunks - 1; chunk >= (int)offset / 64; chunk--)
            {
                chunks[chunk] |= chunks[chunk - offset_outer] << offset_inner;
                if (chunk > offset_outer) {
                    chunks[chunk] |= chunks[chunk - offset_outer - 1] >> (64 - offset_inner);
                }
            }
        }
    }
    void shift_or_r(ull offset)
    {
        int offset_outer = offset / 64;
        int offset_inner = offset % 64;
        bool zero_mod = offset_inner == 0;
        if (zero_mod)
        {
            for (int chunk = 0; chunk < num_chunks - offset_outer; chunk++)
            {
                chunks[chunk] |= chunks[chunk + offset_outer] >> offset_inner;
            }
        }
        else
        {
            for (int chunk = 0; chunk < num_chunks - offset_outer; chunk++)
            {
                chunks[chunk] |= chunks[chunk + offset_outer] >> offset_inner;
                if (chunk + offset_outer + 1 < num_chunks) {
                    chunks[chunk] |= chunks[chunk + offset_outer + 1] << (64 - offset_inner);
                }
            }
        }
    }

};

signed main()
{
    fast();
    
    int n, x;
    cin >> n >> x;
    
    vi nums;
    int ans = 0;
    rep(i, n)
    {
        int l;
        cin >> l;
        ans = max(ans, l);
        if (l <= x) nums.push_back(l);
    }
    if (sz(nums)==0)
    {
        cout << ans;
        return 0;
    }
    if (sz(nums)==1)
    {
        cout << max(ans,nums[0]);
        return 0;
    }
    if (sz(nums)==2)
    {
        cout << max(max(ans,nums[0]), nums[1]);
        return 0;
    }
    if (sz(nums)<=4)
    {
        cout << max(max(ans,x+1), *max_element(nums.begin(), nums.end()));
        return 0;
    }
    sort(nums.rbegin(),nums.rend());
    int r = min(sz(nums), 4LL);
    rep(i, r) ans = max(ans, nums.back()), nums.pop_back();
    n = sz(nums);
    rep(i, n)nums[i] = x + 1 - nums[i];
    int tt = accumulate(nums.begin(),nums.end(),0LL);
    int t = tt/2;

    int s = 0;
    rep(i, n)
    {
        if (s+nums[i]<=t)
        {
            s += nums[i];
            nums[i] = -nums[i];
        }
    }

    mt19937 rng;
    shuffle(nums.begin(), nums.end(), rng);

    const int k = maxv;
    custom_bitset bset;
    bset.enable(k/2);
    repe(num, nums)
    {
        if (num > 0) bset.shift_or(num);
        else bset.shift_or_r(-num);
    }

    int d = t - s;
    int best = inf;
    for (int i = k/2; i < k; i++)
    {
        if (bset.get(i))
        {
            int v = s+i-k/2;
            best = min(best, max(v,tt-v));
        }
    }
    cout << max(ans, x + 1 + best);

    return 0;
}
