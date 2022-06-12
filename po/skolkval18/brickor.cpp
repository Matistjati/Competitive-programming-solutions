#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

#define enablell 0

#define ll long long
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

#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define read3(a,b,c) cin >> a >> b >> c
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
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
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

struct Stringhash
{
    vector<int> suf, b;
    int mod;

    Stringhash(string s, int base = 153, int _mod = 1000000009)
    {
        int n = s.length();
        suf.assign(n + 1, 0); // suf[n] = 0
        b.assign(n + 1, 0);
        b[0] = 1;
        b[1] = base;
        mod = _mod;
        for (int i = n - 1; i >= 0; --i) {
            suf[i] = (s[i] + (ll)suf[i + 1] * b[1]) % mod;
        }
        for (int i = 2; i <= n; ++i) {
            b[i] = (ll)b[i - 1] * b[1] % mod;
        }
    }

    int substr(int l, int r) const // [l, r]
    {
        ll v = suf[l] - (ll)suf[r + 1] * b[r - l + 1];
        v %= mod;
        v += mod;
        v %= mod;
        return v;
    }

    inline static int hashstring(string s, int base = 153)
    {
        int h = 0;
        int b = 1;
        repe(c, s)
        {
            h *= b;
            b *= base;
            h += c - 'b';
        }

        return h;
    }
};

inline int hashs(string s)
{
    int h = 0;
    int b = 1;
    repe(c, s)
    {
        b *= 2;
        h += (c=='V'?0:1)*b;
    }

    return h;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    string othello;
    read(othello);
    string ans(othello.size(), 'V');

    int anshash = hashs(ans);

    vi visited((2<<15)+10);


    int ret = inf;

    queue<pair<string,int>> toCheck;
    toCheck.emplace(othello, 1);

    while (toCheck.size())
    {
        string state;
        int moves;
        tie(state,moves) = toCheck.front();
        toCheck.pop();




        for (int i = 0; i < ans.size() - 2; i++)
        {
            if (state[i] == 'V' && state[i + 1] == 'V')
            {
                continue;
            }
            string c(state);
            string selected;
            selected += (state[i] == 'S') ? 'V' : 'S';
            selected += (state[i + 1] == 'S') ? 'V' : 'S';
            c.erase(i, 2);
            c += selected;

            int shash = hashs(c);
            if (!visited[shash])
            {
                visited[shash] = true;
                toCheck.emplace(c, moves + 1);

                if (shash==anshash)
                {
                    cout << moves;
                    quit;
                }
            }

            c.pop_back();
            c.pop_back();
            c.insert(0, selected);

            shash = hashs(c);
            debif(shash > visited.size());
            if (!visited[shash])
            {
                visited[shash] = true;
                toCheck.emplace(c, moves + 1);

                if (shash == anshash)
                {
                    cout << moves;
                    quit;
                }
            }
        }
    }
    write(ret);


    quit;
}
