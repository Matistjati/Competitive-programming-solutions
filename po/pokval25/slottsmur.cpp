// Python -> C++ using chatgpt + some hand optimization
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


struct Tree {
    typedef p2 T;
    static constexpr T unit = p2(-1, -1);
    T f(T a, T b) { return max(a, b); } // (any associative fn)
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) { // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

int n;

struct SolverBase
{
    vi h;
    SolverBase(vi h) : h(h) {}
    SolverBase() {}
    virtual void update_block(int ind, int w) {};
    virtual ll query(int l, int idx) { return -1; };
};

// Make block_size a compile-time constant
template<int block_size>
struct Solver : public SolverBase
{
    Solver(vi H) : SolverBase(H)
    {
        while (sz(h) % block_size != 0)
        {
            h.push_back(0);
        }
        rep(i, (n + block_size - 1) / block_size) {
            update_block(i * block_size, 0);
        }
    }
    int prefmax[int(2e5) / block_size + 1][block_size];
    ll prefsum[int(2e5) / block_size + 1][block_size];
    ll prefmaxcum[int(2e5) / block_size + 1][block_size];

    void update_block(int ind, int w) override {
        h[ind] += w;
        int block_ind = ind / block_size;
        ind %= block_size;
        int base = block_ind * block_size;
        int p = 0;
        int i = 0;
        if (ind > 0)
        {
            p = prefmax[block_ind][ind - 1];
            i = ind;
        }

        for (; i < block_size; i++) {
            p = max(p, h[base + i]);
            prefmax[block_ind][i] = p;
            prefsum[block_ind][i] = h[base + i];
            prefmaxcum[block_ind][i] = p - h[base + i];
            if (i != 0) {
                prefsum[block_ind][i] += prefsum[block_ind][i - 1];
                prefmaxcum[block_ind][i] += prefmaxcum[block_ind][i - 1];
            }
        }
    }

    inline ll sum_block(int& level, int block, int blocksz)
    {
        ll ret = 0;
        if (level >= prefmax[block][blocksz - 1]) {
            ret += (ll)level * blocksz - prefsum[block][blocksz - 1];
        }
        else {
            int lo = -1, hi = blocksz;
            while (lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if (prefmax[block][mid] >= level) hi = mid;
                else lo = mid;
            }
            ret += (ll)level * (lo + 1) + prefmaxcum[block][blocksz - 1];
            if (lo >= 0) {
                ret -= prefsum[block][lo];
                ret -= prefmaxcum[block][lo];
            }

            level = prefmax[block][blocksz - 1];
        }
        return ret;
    }

    ll query(int l, int idx) override
    {
        ll ans = 0;

        // Left to middle
        int l_block = l / block_size;
        int level = 0;
        for (int i = l; i < min(idx, (l_block + 1) * block_size); ++i) {
            level = max(level, h[i]);
            ans += level - h[i];
        }

        int mid_block = idx / block_size;
        for (int block_ind = l_block + 1; block_ind < mid_block; block_ind++) {
            ans += sum_block(level, block_ind, block_size);
        }

        int modded_ind = idx % block_size;
        if (l_block != mid_block && modded_ind) {
            ans += sum_block(level, mid_block, modded_ind);
        }

        return ans;
    }
};

const int SIZE_1 = 200;
const int SIZE_2 = 270;
const int SIZE_3 = 1200;

inline char gc() { // like getchar()
    static char buf[1 << 16];
    static size_t bc, be;
    if (bc >= be) {
        buf[0] = 0, bc = 0;
        be = fread(buf, 1, sizeof(buf), stdin);
    }
    return buf[bc++]; // returns 0 on EOF
}

int readInt() {
    int a, c;
    while ((a = gc()) < 40);
    if (a == '-') return -readInt();
    while ((c = gc()) >= 48) a = a * 10 + c - 480;
    return a - 48;
}

int main()
{
    fast();

    int q;
    n = readInt();
    q = readInt();

    vi h(n);
    for (int i = 0; i < n; ++i) {
        h[i] = readInt();
    }

    vector<tuple<int, int, int>> queries;
    int num_updates = 0;

    for (int i = 0; i < q; ++i) {
        int t, a, b;
        t = readInt();
        a = readInt();
        b = readInt();
        queries.emplace_back(t, a, b);
        if (t == 2) {
            num_updates++;
        }
    }
    double update_percent = double(num_updates) / q;
    int block_size;
    SolverBase* s;
    SolverBase* rs;
    if (update_percent > 0.65) block_size = SIZE_1;
    else if (update_percent > 0.45) block_size = SIZE_2;
    else block_size = SIZE_3;

    if (block_size == SIZE_1)
    {
        s = new Solver<SIZE_1>(h);
        reverse(all(h));
        rs = new Solver<SIZE_1>(h);
    }
    else if (block_size == SIZE_2)
    {
        s = new Solver<SIZE_2>(h);
        reverse(all(h));
        rs = new Solver<SIZE_2>(h);
    }
    else if (block_size == SIZE_3)
    {
        s = new Solver<SIZE_3>(h);
        reverse(all(h));
        rs = new Solver<SIZE_3>(h);
    }
    else s = rs = 0;
    reverse(all(h));

    Tree tree(n);
    rep(i, n) tree.update(i, p2(h[i], i));

    for (const auto& [t, a, b] : queries)
    {
        if (t == 1)
        {
            int l = a - 1, r = b - 1;
            int idx = tree.query(l, r + 1).second;

            ll tot = s->query(l, idx);
            tot += rs->query(n - r - 1, n - idx - 1);
            cout << tot << "\n";
        }
        else
        {
            int ind = a - 1;

            s->update_block(ind, b);
            rs->update_block(n - ind - 1, b);
            tree.update(ind, { s->h[ind], ind });
        }
    }

    return 0;
}
