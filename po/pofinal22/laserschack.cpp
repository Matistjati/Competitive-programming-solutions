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

#define enablell 1

#define ll long long
#if enablell
#define int ll
#define inf 2e18
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
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s);  string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }

vp2 dirs = { {0,1},{0,-1},{1,0},{-1,0} };
int r, c;

bool possible(vector<string>& board, vvi& smokeTimes, p2 king, p2 source, int t)
{
    if (smokeTimes[king.second][king.first] <= t)
    {
        return true;
    }

    queue<p2> toDo;
    toDo.emplace(source);

    vvb visited(board.size(), vb(board[0].size()));

    while (toDo.size())
    {
        p2 curr = toDo.front();
        toDo.pop();

        if (visited[curr.second][curr.first]) continue;
        visited[curr.second][curr.first] = true;

        repe(dir, dirs)
        {
            p2 p = curr;
            rep(i, 1e5)
            {
                if (!within(p.first, c, p.second, r)) break;

                char c = board[p.second][p.first];

                if (smokeTimes[p.second][p.first] <= t)
                {
                    break;
                }
                if (c=='o')
                {
                    toDo.emplace(p);
                }
                else if (c=='K')
                {
                    return false;
                }

                p.first += dir.first;
                p.second += dir.second;
            }
        }

    }


    return true;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    read2(r, c);



    vector<string> board(r);
    rep(i, r)
    {
        dread(string, row);
        board[i] = row;
    }


    p2 king = mp(-1, -1);
    p2 source = mp(-1, -1);

    queue<p3> clouds;

    rep(i, r)
    {
        rep(j, c)
        {
            if (board[i][j]=='K')
            {
                king = { j,i };
            }
            else if (board[i][j] == 'A')
            {
                source = { j,i };
            }
            else if (board[i][j]=='R')
            {
                clouds.emplace(j, i, 0);
            }
        }
    }

    vvi smokeTime(r, vi(c,-1));



    while (clouds.size())
    {
        int x, y, t;
        tie(x, y, t) = clouds.front();
        clouds.pop();

        if (smokeTime[y][x] != -1) continue;

        smokeTime[y][x] = t;

        repe(dir, dirs)
        {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (!within(nx,c,ny,r))
            {
                continue;
            }

            clouds.emplace(nx, ny, t + 1);
        }
    }

    int low = 0;
    int high = 1e6;

    while (true)
    {
        int t = (low + high) / 2;
        bool p = possible(board, smokeTime, king, source, t);

        if (p)
        {
            high = t;
        }
        else
        {
            low = t+1;
        }

        if (low==high)
        {
            cout << low;
            quit;
        }
    }

    quit;
}