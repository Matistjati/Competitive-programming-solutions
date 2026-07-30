#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define repe(i, arr) for (auto& i : arr)
#define rep(i, b) for(ll i = 0; i < (b); ++i)
#define repp(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)x.size())

#define NO_INLINE 0

struct Bitset {
    using ull = unsigned long long;
    int n;
    int num_blocks;
    vector<ull> blocks;
    Bitset(int n) : n(n), num_blocks((n + 63) / 64), blocks(num_blocks) {

    }

#if NO_INLINE
    __attribute__((noinline))
#endif
    int find_last() {
        for (int i = num_blocks - 1; i >= 0; i--) {
            ull b = blocks[i];
            if (b > 0) {
                int pos = 63 - countl_zero(b);
                int idx = i * 64 + pos;
                assert(idx < n);
                return idx;
            }
        }
        assert(false);
    }

    void set(int x) {
        blocks[x / 64] |= 1ULL << (x % 64);
    }
    void unset(int x) {
        blocks[x / 64] &= ~(1ULL << (x % 64));
    }
    int get(int x) {
        return (blocks[x / 64] & (1ULL << (x % 64))) > 0;
    }
};

static constexpr int MAX_NUM_KEYS = 650;
struct Heap // heap
{
    int n;
    vector<int> my_freq;
    vi free_slots;
    vector<Bitset> bitsets;
    vector<int> popcount;
    vector<int> which_bitset;
    Bitset active_freq;

#if NO_INLINE
    __attribute__((noinline))
#endif
    void insert(int val)
    {
        int freq = my_freq[val];
        if (which_bitset[freq] == -1) { // claim a fresh bitset
            //assert(sz(free_slots));
            int slot = free_slots.back();
            free_slots.pop_back();
            which_bitset[freq] = slot;
            active_freq.set(freq);
        }
        int bind = which_bitset[freq];
        Bitset& bset = bitsets[bind];
        //assert(bset.get(val) == 0);
        bset.set(val);
        popcount[bind]++;
    }

#if NO_INLINE
    __attribute__((noinline))
#endif
    void remove(int val)
    {
        int freq = my_freq[val];
        int bind = which_bitset[freq];

        //assert(bind != -1);
        Bitset& bset = bitsets[bind];
        //assert(bset.get(val) == 1);

        bset.unset(val);
        popcount[bind]--;
        if (popcount[bind] == 0) { // reclaim
            which_bitset[freq] = -1;
            free_slots.push_back(bind);
            active_freq.unset(freq);
        }
    }

#if NO_INLINE
    __attribute__((noinline))
#endif
    void change_freq(int country, int add) {
        remove(country);
        my_freq[country] += add;
        insert(country);
    }
    Heap(int n, int max_freq) : my_freq(n), bitsets(MAX_NUM_KEYS, Bitset(n)),
        popcount(MAX_NUM_KEYS), which_bitset(max_freq + 1, -1), active_freq(max_freq + 1) {
        //assert(n >= MAX_NUM_KEYS);
        rep(i, MAX_NUM_KEYS) free_slots.push_back(i);
        rep(i, n) insert(i);
    }

    int best() {
        int highest_freq = active_freq.find_last();
        int bind = which_bitset[highest_freq];
        Bitset& bset = bitsets[bind];
        return bset.find_last();
    }
};




int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, t, q;
    cin >> n >> t >> q;
    vector<tuple<int, int, int>> islands;

    rep(i, t)
    {
        int s, c;
        cin >> c >> s;
        c--;
        islands.emplace_back(s, c, i);
    }

    vector<p2> queries(q);
    int update_ind = 0;
    rep(i, q)
    {
        char c;
        cin >> c;
        if (c == '=')
        {
            int ind, s;
            cin >> ind >> s;
            ind--;

            queries[i] = { ind,s };
            islands.emplace_back(s, get<1>(islands[ind]), t + update_ind++);
        }
        else
        {
            int lim;
            cin >> lim;
            queries[i] = { lim,-1 };
        }
    }


    sort(all(islands));
    reverse(all(islands));
    vi where_to(sz(islands));
    rep(i, sz(islands)) where_to[get<2>(islands[i])] = i;
    struct Island
    {
        int size, country;
    };

    vector<Island> clean_islands;
    for (auto [size, country, _] : islands)
    {
        clean_islands.push_back({ size,country });
    }

    int query_ind = 0;
    vector<tuple<int, int, int>> query_pts;
    vi next_ind(sz(islands), -1);
    vi head(sz(islands), -1);
    rep(i, t) head[i] = i;
    vector<p2> updates;
    update_ind = 0;
    rep(i, sz(queries))
    {
        if (queries[i].second == -1) // query
        {
            auto [size, _] = queries[i];
            query_pts.emplace_back(size, sz(updates) - 1, query_ind++);
        }
        else // update
        {
            auto [ind, s] = queries[i];

            int h = head[ind];
            next_ind[h] = t + update_ind;
            head[ind] = t + update_ind;

            updates.emplace_back(where_to[h], where_to[t + update_ind]); // disable h, enable t+i
            update_ind++;
        }
    }

    vi island_sizes;
    for (auto [size, country] : clean_islands) island_sizes.push_back(size);
    sort(all(island_sizes));
    island_sizes.push_back(INT_MAX);
    for (auto& [size, _, __] : query_pts) {
        size = lower_bound(all(island_sizes), size) - begin(island_sizes);
    }
    const int B = 500;
    auto norm = [&](tuple<int, int, int> a) {
        int size = get<0>(a);
        int update_ind = get<1>(a);
        ll which_update_block = ll(update_ind) / B;
        return which_update_block * 1e6 + ((which_update_block % 2 == 0) ? size : -size);
    };
    auto comp = [&](tuple<int, int, int> a, tuple<int, int, int> b) {
        return norm(a) < norm(b);
    };

    sort(all(query_pts), [&](tuple<int, int, int> a, tuple<int, int, int> b)
    {
        return comp(a, b);
    });

    for (auto& [size, _, __] : query_pts) {
        size = island_sizes[size];
    }

    //sort(all(pts));
    vi ans(query_ind, -1);

    vi freq(n);
    Heap heap(n, t);

    p2 pos = { -1,-1 };
    vi enabled(sz(islands));
    rep(i, t) enabled[where_to[i]] = 1;
    clean_islands.push_back({ INT_MIN, -1 });
    ll tot_steps = 0;
    for (auto [island_size, update_amnt, qind] : query_pts)
    {

        auto add_update = [&]()
        {
            pos.second++;
            auto [disable, enable] = updates[pos.second];
            int country = clean_islands[disable].country;
            assert(country == clean_islands[enable].country);
            if (clean_islands[disable].size >= island_size && clean_islands[enable].size >= island_size)
            {

            }
            else if (clean_islands[disable].size >= island_size)
            {
                heap.change_freq(country, -1);
            }
            else if (clean_islands[enable].size >= island_size)
            {
                heap.change_freq(country, +1);
            }
            enabled[disable] = 0;
            enabled[enable] = 1;
        };

        auto remove_update = [&]()
        {
            auto [disable, enable] = updates[pos.second];
            int country = clean_islands[disable].country;
            assert(country == clean_islands[enable].country);
            if (clean_islands[disable].size >= island_size && clean_islands[enable].size >= island_size)
            {

            }
            else if (clean_islands[disable].size >= island_size)
            {
                heap.change_freq(country, +1);
            }
            else if (clean_islands[enable].size >= island_size)
            {
                heap.change_freq(country, -1);
            }
            enabled[disable] = 1;
            enabled[enable] = 0;
            pos.second--;
        };

        auto remove_bound = [&]()
        {
            auto [size, country] = clean_islands[pos.first];
            if (enabled[pos.first])
            {
                heap.change_freq(country, -1);
            }
            pos.first--;
        };

        auto add_bound = [&]()
        {
            pos.first++;
            auto [size, country] = clean_islands[pos.first];
            if (enabled[pos.first])
            {
                heap.change_freq(country, +1);
            }
        };
        while (clean_islands[pos.first + 1].size >= island_size)
        {
            add_bound();
            tot_steps++;
        }
        while (pos.first != -1 && clean_islands[pos.first].size < island_size)
        {
            remove_bound();
            tot_steps++;
        }
        while (pos.second < update_amnt)
        {
            add_update();
            tot_steps++;
        }
        while (pos.second > update_amnt)
        {
            remove_update();
            tot_steps++;
        }

        ans[qind] = heap.best();
    }

    repe(v, ans)
    {
        assert(v != -1);
        cout << v + 1 << '\n';
    }
    cerr << "Total steps: " << tot_steps << '\n';
    cerr << "Total points: " << sz(query_pts) << '\n';
    cerr << "x width: " << sz(clean_islands) << ", y width: " << sz(updates) << '\n';

    return 0;
}
