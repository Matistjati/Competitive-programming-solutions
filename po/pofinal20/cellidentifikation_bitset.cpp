#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens

#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

#define enablell 0

#define ll long long
#if enablell
#define int ll
#define inf 2e18
#else
#define inf int(2e9)
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define p2 pair<int, int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vvvp2 vector<vvp2>
#define p3 tuple<int,int,int>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define p4 tuple<int,int,int,int>
#define vp4 vector<p4>

#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#define debassert(expr) if (!(expr)) deb;
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debassert(expr) ;
#define debif(expr) ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high; i >= 0; i--)
#define perr(i, low, high) for (int i = high; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define rununtil(time) if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

template <typename T, typename U> void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

constexpr const int maxv = int(2e5+10);
const int padded_size = maxv + 64 - maxv % 64;
constexpr const int num_chunks = int(padded_size / 64);
constexpr const int mask_64 = 63;

#if _LOCAL
#define __builtin_ctzll _lzcnt_u64
#endif

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
        int outer_index = ind >> 6;
        int inner_index = ind & mask_64;
        chunks[outer_index] |= (1ull << inner_index);
    }
    void operator&=(const custom_bitset& other)
    {
        rep(i, num_chunks)
        {
            chunks[i] &= other.chunks[i];
        }
    }
    void set_1()
    {
        rep(i, num_chunks)
        {
            chunks[i] = ~(0ULL);
        }
    }
    int Find_first(int offset = 0)
    {
        int ret = inf;
        repp(i, offset, num_chunks)
        {
            if (chunks[i])
            {
#if _LOCAL
                return i * 64 + 64 - __builtin_ctzll(chunks[i]);
#else
                return i * 64 + __builtin_ctzll(chunks[i]) + 1;
#endif
            }
        }
        return ret;
    }
    int count()
    {
        int ret = 0;
        rep(i, num_chunks-1)
        {
            ret += popcount(chunks[i]);
        }
        constexpr int pad = 64 - maxv % 64;
        ret += popcount(chunks.back()&((1ULL<<pad)-1));
        return ret;
    }
};

int32_t main()
{
    fast();

    dread2(int, n, k);

    vi types(n);


    vector<custom_bitset> sets(k);

    rep(i, n)
    {
        dread(string, type);
        types[i] = stoi(type, 0, 2);
        rep(j, k)
        {
            if (type[j] == '1')
            {
                sets[j].enable(i);
            }
        }
    }

    int leftHigh = k / 2;
    int rightLow = k / 2 + 1;
    int rightHigh = k;
    int n_right = rightHigh - rightLow + 1;
    vector<custom_bitset> left(1 << leftHigh);
    vector<custom_bitset> right(1 << (n_right));

    rep(i, 1 << leftHigh)
    {
        custom_bitset possible;
        possible.set_1();
        rep(j, leftHigh)
        {
            if (i & (1 << (leftHigh - j - 1)))
            {
                possible &= sets[j];
            }
        }
        left[i] = possible;

    }

    rep(i, 1 << n_right)
    {
        custom_bitset possible;
        possible.set_1();
        repp(j, leftHigh, rightHigh)
        {
            if (i & (1 << (rightHigh - j - 1)))
            {
                possible &= sets[j];
            }
        }
        right[i] = possible;

    }

    dread(int, q);
    
    custom_bitset possible;
    if (k==1)
    {
        while (q--)
        {
            dread(string, queryS);

            int query = stoi(queryS, 0, 2);
            int match = -1;
            int n_matches = 0;

            rep(i, n)
            {
                if ((types[i] & query) == query)
                {
                    match = i;
                    n_matches++;
                }
            }

            if (n_matches == 0) cout << "finns ej";
            else if (n_matches == 1) cout << match+1;
            else cout << "vet ej";
            cout << "\n";
        }
        return 0;
    }
    while (q--)
    {
        dread(string, queryS);

        int leftPart = stoi(queryS.substr(0, leftHigh), 0, 2);
        int rightPart = stoi(queryS.substr(leftHigh), 0, 2);

        possible.set_1();

        possible &= left[leftPart];
        possible &= right[rightPart];


        if (possible.count() == 0) cout << "finns ej";
        else if (possible.count() == 1) cout << possible.Find_first();
        else cout << "vet ej";
        cout << "\n";
    }
    

    quit;
}
