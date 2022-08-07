#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>

using namespace std;

#define enablell 0

typedef long long ll;
#if enablell
#define int ll
#define inf LLONG_MAX
#define float double
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

//#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define read3(a,b,c) cin >> a >> b >> c
//#define write(a) cout << (a) << "\n"
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
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))
#define indexpair(p, i) ((i==0)?p.first:p.second)
#define chmax(a,b) ((a)=max((a),b))
#define chmin(a,b) ((a)=min((a),b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
inline int readintsigned() { int v = 0; int sign = 1; char c = getchar(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v * sign; }
inline int readint() { int v = 0; char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v; }
inline string readstring() { string s; char c; while ((c = getchar()) != EOF && c != '\n') { s.push_back(c); } return s; }
#if _MSC_VER > 0
#define gc() getchar()
#define popcount(x) __popcnt(x)
#define assert(x) debassert(x)
#else
#define popcount(x) __builtin_popcount(x)
#define gc() getchar_unlocked()
#if 0
#include <bits/extc++.h>
using namespace __gnu_pbds;
#endif
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return x; }
};
//typedef __gnu_pbds::gp_hash_table<int, null_type, chash> h;

#endif

inline int hamming_distance(vi a, vi b)
{
    assert(a.size() == b.size());
    int ret = 0;
    rep(i, a.size())
    {
        ret += popcount(a[i] ^ b[i]);
    }

    return ret;
}

vi find_key_size(vi& bytes)
{
    const int max_key_len = 15;
    int hamming_blocks = int(bytes.size() * 0.06);

    vector<pair<double, int>> keys(max_key_len + 1);

    assert(hamming_blocks * max_key_len < bytes.size());


    repp(key_len, 1, max_key_len + 1)
    {
        vvi blocks;

        rep(i, hamming_blocks)
        {
            vi block;

            for (int j = i * key_len; j < (i + 1) * key_len; j++) block.emplace_back(bytes[j]);

            blocks.emplace_back(block);
        }

        double tot = 0;
        int n = 0;

        rep(i, blocks.size() - 1)
        {
            repp(j, i, blocks.size())
            {
                tot += hamming_distance(blocks[i], blocks[j]);
                n++;
            }
        }
        tot /= n;
        keys[key_len].first = tot;
        keys[key_len].second = key_len;
    }
    keys[0].first = inf;

    sort(all(keys));

    vi ret(keys.size());
    rep(i, keys.size()) ret[i] = keys[i].second;

    return ret;
}


bool works(vi& text, int offset, int keylen, int key)
{
    vi distribution(256);
    for (int i = offset; i < text.size(); i += keylen) distribution[text[i] ^ key]++;

    // Sort out obviously wrong characters
    int tot = 0;
    rep(i, 256)
    {
        if (!isspace(i) && !isprint(i) && distribution[i])
        {
            return false;
        }
        tot += distribution[i];
    }

    if (distribution[' '] < tot / 15) return false;
    if (distribution['|'] + distribution['~'] > 20) return false;

    // If fisk testcase, does not follow normal grammar heuristics
    string fisk = "FISK";
    int fishes = 0;
    rep(i, 4) fishes += distribution[fisk[i]] + distribution[tolower(fisk[i])];
    if ((fishes + 0.) / tot > 0.5) return true;

    // If it contains more than 5% punctuation, it's probably wrong
    string punctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~;";

    int n_punctuation = 0;
    repe(c, punctuation) n_punctuation += distribution[c];
    if (n_punctuation * 10 > tot) return false;

    int num_lowercase = 0;
    for (int i = 'a'; i <= 'z'; i++) num_lowercase += distribution[i];
    int num_uppercase = 0;
    for (int i = 'A'; i <= 'Z'; i++) num_uppercase += distribution[i];

    // If more than 10% is uppercase, it's probably wrong
    if (num_uppercase * 5 > num_lowercase) return false;
    if (num_uppercase + num_lowercase+distribution[' ']+distribution['\n'] < 0.9*tot) return false;

    int unlikely = 0;
    if (distribution['e'] < num_lowercase / 26) unlikely++;
    if (distribution['a'] < num_lowercase / 26) unlikely++;
    if (distribution['t'] < num_lowercase / 26) unlikely++;
    if (distribution['i'] < num_lowercase / 26) unlikely++;
    if (distribution['o'] < num_lowercase / 26) unlikely++;

    if (unlikely > 1) return false;

    return true;
}

int todec(char i)
{
    if (isdigit(i)) return i - '0';
    else if ('a' <= i && i <= 'f') return i - 'a' + 10;
    else assert(false);
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\joshua.jeffmarander\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

#if 0
    string input, temp;
    while (cin >> temp) input += temp;
#else
    dread(string, input);
#endif
    vi bytes;

    for (int i = 0; i < input.size(); i += 2)
    {
        // Hex to decimal


        bytes.push_back(todec(input[i]) * 16 + todec(input[i + 1]));
        //assert(bytes[bytes.size() - 1] >= 0 && bytes[bytes.size() - 1] < 128);
    }

    vi keylens = find_key_size(bytes);

    rep(i, 10)
    {

        vvi keys;

        rep(offset, keylens[i])
        {
            vi block_keys;

            rep(key, 255)
            {
                if (works(bytes, offset, keylens[i], key)) block_keys.emplace_back(key);
            }

            keys.emplace_back(block_keys);
        }


        vi finalkeys;
        rep(j, keys.size())
        {
            if (keys[j].size() == 0) goto end;
            else if (keys[j].size() > 1) goto end;
            finalkeys.emplace_back(keys[j][0]);
        }

        rep(j, bytes.size())
        {
            cout << char(bytes[j] ^ finalkeys[j % finalkeys.size()]);
        }
        return 0;
    end:;
    }

    return 0;
    quit;
}