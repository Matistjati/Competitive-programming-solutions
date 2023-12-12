#pragma GCC optimize("Ofast,inline,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#define enablell 1

typedef long long ll;
typedef unsigned long long ull;
#if enablell
#define int ll
#define inf int(1e18)
#else
const int inf = int(2e9);
#endif
typedef vector<ull> vull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef pair<int, int> p2;
typedef vector<p2> vp2;
typedef vector<vp2> vvp2;
typedef vector<vvp2> vvvp2;
typedef tuple<int, int, int> p3;
typedef vector<p3> vp3;
typedef vector<vp3> vvp3;
typedef vector<vvp3> vvvp3;
typedef tuple<int, int, int, int> p4;
typedef vector<p4> vp4;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

#define _LOCAL _MSC_VER > 0
#if _LOCAL

#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
uint32_t ctz(uint32_t x) { return _tzcnt_u32(x); }
#else
#define popcount(x) __builtin_popcountll(x)
uint32_t ctz(uint32_t x) { return __builtin_ctzll(x); }

#if 0
namespace pbds
{
    using namespace __gnu_pbds;

    template<typename T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
    template<typename T, typename U> using indexed_map = tree<T, U, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

    struct chash { // large odd number for C
        const uint64_t C = ll(4e18 * acos(0)) | 71;
        ll operator()(ll x) const { return __builtin_bswap64(x * C); }
    };
    template<typename T, typename U> using fast_map = __gnu_pbds::gp_hash_table<T, U, chash>;
    template<typename T> using fast_set = __gnu_pbds::gp_hash_table<T, null_type, chash>;
    template<typename T, typename H> using fast_set_h = __gnu_pbds::gp_hash_table<T, null_type, H>;
}
using namespace pbds;
#endif
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
#define FAST_INPUT 0
#if FAST_INPUT && !_LOCAL
#define gc() getchar_unlocked()
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) && c != ' ' && c != '\n') { if (c == EOF) { v = -1; return; } v *= 10; v += c - '0'; } v *= sign; }
inline void read(int& u, int& v) { read(u); read(v); }
inline void read(int& u, int& v, int& k) { read(u); read(v); read(k); }
//inline void read(int& v) { char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } }
inline void read(string& s) { char c; while ((c = gc()) != EOF && c != '\n' && c != ' ') { s.push_back(c); } }
inline void readline(string& s) { char c; while ((c = gc()) != EOF && c != '\n') { s.push_back(c); } }
#else
template <typename T> inline void read(T& a) { cin >> a; }
inline void read(p2& a) { cin >> a.first >> a.second; }
#endif

#define quit cout << flush; _Exit(0);
void readinput() {} // Recursion base case
template<typename T, typename... Args> void readinput(T& arg, Args&... args) { read(arg); readinput(args...); }
#define dread(type, ...) type __VA_ARGS__; readinput(__VA_ARGS__);
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (T& u : v) read(u); return is; }
#define _ << " " <<

#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#define debassert(expr) if(!(expr)) deb;
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debif(expr) ;
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)
ll binpow(ll a, ll b) { ll res = 1; while (b > 0) { if (b & 1) res = res * a; a = a * a; b >>= 1; } return res; }
ll binpow(ll a, ll b, ll m) { a %= m; long long res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } return res; } // For a < 2^31

template <typename T, typename U> inline void operator+=(pair<T, U>& l, const pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator+(const pair<T, U> l, const pair<T, U> r) { return { l.first + r.first, l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator-(const pair<T, U> l, const pair<T, U> r) { return { l.first - r.first, l.second - r.second }; }
template <typename T, typename U> inline pair<T, U> operator*(const pair<T, U> l, const int m) { return { l.first * m, l.second * m }; }
vector<string> split(string s, string d) { size_t k = 0, n, e = d.length(); string t; vector<string> r; while ((n = s.find(d, k)) != string::npos) { t = s.substr(k, n - k); k = n + e; r.push_back(t); } r.push_back(s.substr(k)); return r; }

#if 1
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]
#endif
const ll mod = 1e9 + 7;
vp2 dirs = { {0,1},{0,-1},{1,0},{-1,0} };

struct guessinfo
{
    vp2 disallowed;
    vp2 forced;
    vp2 characterlimits;

    bool mightmatch(string other)
    {

        repe(u, forced)
        {
            if (other[u.first] != u.second) return 0;
        }

        repe(u, disallowed)
        {
            if (other[u.first] == u.second) return 0;
        }

        map<char, int> cnt;
        repe(c, other) cnt[c]++;
        repe(lim, characterlimits)
        {
            int c, l;
            tie(c, l) = lim;
            if (!setcontains(cnt, c)) return 0;
            if (cnt[c] < l) return 0;
        }

        return 1;
    }
    bool won() { return forced.size() == 5; }
};


string correct_word;
string fillguess(string guess, string correct_word)
{
    vector<char> color(5, 'X');
    map<char, int> count;
    for (int i = 0; i < 5; i++) {
        if (guess[i] == correct_word[i]) {
            color[i] = 'O';
        }
        else {
            count[correct_word[i]]++;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (guess[i] != correct_word[i] && count[guess[i]] > 0) {
            color[i] = '/';
            count[guess[i]]--;
        }
    }
    string c(color.begin(), color.end());
    return c;
}
#if 0

#else
map<string, string> cache;
string makeguess(string g)
{
    if (setcontains(cache, g)) return cache[g];
    cout << g << endl;
    //string response = fillguess(g, correct_word);
    dread(string, response);
    if (response == "OOOOO")
    {
        exit(0);
    }
    return cache[g] = response;
}
#endif



guessinfo getinfo(string g, string response)
{
    guessinfo info;

    map<char, int> guesscnt;
    map<char, int> realcnt;

    rep(i, g.size())
    {
        realcnt[g[i]]++;
        if (response[i] == 'O')
        {
            guesscnt[g[i]]++;
            info.forced.emplace_back(i, g[i]);
        }
        if (response[i] == '/')
        {
            guesscnt[g[i]]++;
        }
        if (response[i] == 'X')
        {
            info.disallowed.emplace_back(i, g[i]);
        }
    }

    repe(g, guesscnt)
    {
        info.characterlimits.emplace_back(g.first, g.second);
    }

    return info;
}

map<pair<int, set<string>>, pair<string, double>> dp;
pair<string, double> bestguess(set<string> words, int depth)
{
    pair<int, set<string>> state = { depth , words };
    if (setcontains(dp, state)) return dp[state];
    if (words.size() <= 1) return { "", 0 };
    if (depth >= 2) return { "",words.size() };

    string bestword;
    double bestscore = inf;
    repe(w, words)
    {
        double score = 0;
        repe(resp, words)
        {
            guessinfo info = getinfo(w, fillguess(w, resp));

            int k = 0;
            set<string> newwords;
            repe(w3, words)
            {
                if (info.mightmatch(w3) && w3 != w) newwords.insert(w3);
            }
            score += bestguess(newwords, depth + 1).second;
        }
        if (score < bestscore)
        {
            bestscore = score;
            bestword = w;
        }
    }
    return dp[state] = { bestword,bestscore };
}

string getsmall(vector<string> words)
{
    cerr << "get small " << endl;
    dp = map<pair<int, set<string>>, pair<string, double>>();
    string res = bestguess(set<string>(all(words)), 0).first;
    cerr << "dp size:" << dp.size() << endl;
    return res;
}

string getlarge(vector<string> words)
{
    string bestword;
    double bestscore = inf;
    sort(all(words));
    vector<pair<int, string>> ws;
    repe(w, words)
    {
        double score = 0;

        repe(w2, words)
        {
            rep(i, 5) score += w[i] == w2[i];
        }

        ws.emplace_back(score, w);
    }
    sort(all(ws));
    return ws[ws.size() / 10].second;
}

string getguess(vector<string> words)
{
    if (words.size() == 1) return words[0];
    if (words.size() > 100) return getlarge(words);
    string bestword;
    double bestscore = inf;

    repe(w, words)
    {
        double score = 0;

        repe(w2, words)
        {
            guessinfo info = getinfo(w, fillguess(w, w2));

            int k = 0;
            vector<string> newwords;
            repe(w3, words)
            {
                if (info.mightmatch(w3)) k++;
            }
            score += pow(k, 1.5);// max(score, (double)k);
        }
        score /= words.size();
        if (score < bestscore)
        {
            bestscore = score;
            bestword = w;
        }
    }
    cerr << "score:" << bestscore << "\n";

    return bestword;
}

int32_t main()
{
    fast();
#if 0 && _LOCAL
    ifstream instream("C:\\users\\matis\\source\\repos\\comp_prog\\x64\\debug\\in.txt");
    cin.rdbuf(instream.rdbuf());
#endif


#if 1
    dread(int, n);
    vector<string> words(n);
    cin >> words;
#else
    int n = 30;// randint(10, 500);
    vector<string> words(n);
    rep(i, n)
    {
        rep(j, 5) words[i].push_back((char)randint('a', 'z'));
    }
#endif
    set<string> origwords(all(words));
    correct_word = randel(words);

    while (true)
    {
        assert(words.size());
        string g = getguess(words);
        //assert(setcontains(origwords, g));
        guessinfo info = getinfo(g, makeguess(g));

        vector<string> newwords;
        repe(w, words)
        {
            if (info.mightmatch(w) && w != g) newwords.push_back(w);
        }
        words = newwords;
    }

    quit;
}