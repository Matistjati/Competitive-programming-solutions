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
#define debassert(expr) if(!(expr)) deb;
#else
#define noop ;
#define deb ;
#define debif(expr) ;
#define debassert(expr) ;
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
inline string readstring() { string s; char c; while ((c = getchar()) != '\n') { s.push_back(c); } return s; }

int t, n, m;
vector<string> grid;
vector<string> in;
vi rowsums;
vvb canmove;

#ifdef _DEBUG
#define tm 2500
#else
#define tm 15000
#endif

ll eval(vector<string>& grid)
{
    ll errs = 0;
    rep(i, n) rep(j, m)
    {
        assert(grid[i][j] == 'x' || grid[i][j] == 'o');

        char c = grid[i][j];

        if (j >= 2 && grid[i][j - 1] == c && grid[i][j - 2] == c) errs++;
        if (i >= 2 && grid[i - 1][j] == c && grid[i - 2][j] == c) errs++;
        if (i >= 2 && j >= 2 && grid[i-1][j-1] == c && grid[i-2][j-2] == c) errs++;
        if (i + 2 < n && j >= 2 && grid[i+1][j-1] == c && grid[i+2][j-2] == c) errs++;
    }

    return errs;
}

vp2 dirs = { {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} };

inline int countarea(int x, int y)
{
    int errs = 0;

    repe(dir, dirs)
    {
        // d = dot. p2 already taken :(
        p2 d1 = { x,y };
        p2 d2 = d1;
        d2 += dir;
        p2 d3 = d2;
        d3 += dir;

        if (!within(d3.first, n, d3.second, m)) continue;

        char c = grid[d1.first][d1.second];
        if (c == grid[d2.first][d2.second] && c == grid[d3.first][d3.second]) errs++;
    }

    return errs;
}

void placestupid()
{
    rep(i, n)
    {
        int x = count(all(grid[i]), 'x');

        while (x< rowsums[i])
        {
            while (true)
            {
                int idx = rand() % m;
                if (grid[i][idx] == '.')
                {
                    grid[i][idx] = 'x';
                    x++;
                    break;
                }
            }
        }

        rep(j, m)
        {
            if (grid[i][j] == '.') grid[i][j] = 'o';
        }
    }
}

void placeempty()
{
    rep(i, n)
    {
        int x = 0;
        vector<char> symbols = { 'x','o' };
        if (i % 4 > 1) swap(symbols[0], symbols[1]);

        rep(j, m)
        {
            if (x < rowsums[i])
            {
                grid[i][j] = symbols[j % 2];
                x+=(symbols[j%2]=='x');
            }
            else
            {
                grid[i][j] = 'o';
            }
        }

        while (x < rowsums[i])
        {
            int j = rand() % m;
            if (grid[i][j] == 'o')
            {
                grid[i][j] = 'x';
                x++;
            }
        }

        debassert(x == rowsums[i]);
        debassert(count(all(grid[i]), 'x') == x);
    }
}

int countrow(int i)
{
    return count(all(grid[i]), 'x');
}

void placealmostempty()
{
    rep(i, n)
    {
        int x = countrow(i);
        vector<char> symbols = { 'x','o' };
        if (i % 4 > 1) swap(symbols[0], symbols[1]);

        rep(j, m)
        {
            if (grid[i][j] != '.') continue;

            if (x < rowsums[i])
            {
                grid[i][j] = symbols[j % 2];
                x += (symbols[j % 2] == 'x');
            }
            else
            {
                grid[i][j] = 'o';
            }
        }

        while (x < rowsums[i])
        {
            int j = rand() % m;
            if (grid[i][j] == '.' || (canmove[i][j]&&grid[i][j]=='o'))
            {
                grid[i][j] = 'x';
                x++;
            }
        }

        rep(j, m) if (grid[i][j] == '.') grid[i][j] = 'o';

        debassert(x == rowsums[i]);
        debassert(count(all(grid[i]), 'x') == x);
    }
}

void hillclimb()
{
    ll score = eval(grid);


    rep(i, n)
    {
        rep(j, m)
        {
            #pragma GCC ivdep
            #pragma GCC unroll 25
            rep(l, 50)
            {
                int a = i;
                int b = rand() % m;

                if (!canmove[i][j] || !canmove[a][b] || grid[i][j] == grid[a][b]) continue;

                //int evalbef = eval(grid);
                int a1 = countarea(i, j);
                int a2 = countarea(a, b);

                swap(grid[i][j], grid[a][b]);

                int b1 = countarea(i, j);
                int b2 = countarea(a, b);

                ll newscore = score - a1 - a2 + b1 + b2;
                //debassert(newscore == eval(grid));
                if (newscore < score)
                {
                    score = newscore;
                }
                else
                {
                    swap(grid[i][j], grid[a][b]);
                }
            }
            if (elapsedmillis() >= tm) return;
        }
    }

}

void checkgrid()
{
    rep(i, n)
    {
        rep(j,m) debassert(grid[i][j] != '.');
        debassert(count(all(grid[i]), 'x') == rowsums[i]);
        rep(j, m) debassert(in[i][j] == '.' || in[i][j] == grid[i][j]);
    }
}

int32_t main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\desktop\\kryssring\\attachments\\5.in");
#endif

    read(t);

    //if (t != 1) return 0;

    read2(n, m);

    rowsums = vi(n);
    rep(i, n) read(rowsums[i]);

    grid = vector<string>(n);
    rep(i, n) read(grid[i]);

    in = vector<string>(grid);

    canmove = vvb(n, vb(m));

    rep(i, n) rep(j, m) if (grid[i][j] == '.') canmove[i][j] = true;

    if (t==10)
    {
        placeempty();
    }
    else
    {
        placealmostempty();
    }


    checkgrid();

    while (true)
    {
        hillclimb();
        if (elapsedmillis() >= tm) break;
    }

    checkgrid();

    rep(i, n)
    {
        assert(count(all(grid[i]), 'x') == rowsums[i]);
        rep(j, m) assert(in[i][j] == '.' || in[i][j] == grid[i][j]);
        rep(j, m)
        {
            cout << grid[i][j];
        }
        cout << "\n";
    }

    //cout << eval(grid);

    //cout << countgrid(grid);



    quit;
}
