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
inline string readstring() { string s; char c; while ((c = getchar()) != EOF && c != '\n') { s.push_back(c); } return s; }

vp2 diagonal = { {1, -1}, {1,1}, {-1,1},{-1,-1} };
vp2 cross = { {1,0},{-1,0},{0,1},{0,-1} };
vp2 queen = { {1, -1}, {1,1}, {-1,1},{-1,-1}, {1,0},{-1,0},{0,1},{0,-1} };
vp2 knight = { {1,2},{1,-2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,1},{-2,-1} };

vi is_black(129);
vi is_white(129);

vector<string> board;

typedef pair<p2, char> piece;


struct action
{
    piece from;
    piece to;
};
typedef vector<action> va;

stack<action> moves;

void domove(p2 from, p2 to)
{
    moves.push({ {from, board[from.second][from.first]},{to, board[to.second][to.first]} });
    board[to.second][to.first] = board[from.second][from.first];
    board[from.second][from.first] = '.';
}

void undomove()
{
    action m = moves.top();
    moves.pop();
    board[m.from.first.second][m.from.first.first] = m.from.second;
    board[m.to.first.second][m.to.first.first] = m.to.second;
}

bool inside_board(p2& pos)
{
    return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
}

va movedir(vp2& dirs, p2 pos, int limit, bool white, bool pawn = false)
{
    va ret = {};

    bool pieceWhite = is_white[board[pos.second][pos.first]];

    repe(dir, dirs)
    {
        repp(i, 1, limit + 1)
        {
            p2 np = pos;
            np.first += dir.first * i;
            np.second += dir.second * i;

            if (!inside_board(np)) break;

            char c = board[np.second][np.first];
            if (c == '.')
            {
                if (pawn && dir.first != 0) break;
                action p = { { pos,board[pos.second][pos.first] }, { np,c } };
                ret.emplace_back(p);
            }
            else if (pieceWhite && is_white[c] || (!pieceWhite && is_black[c]))
            {
                break;
            }
            else
            {
                if (pawn && dir.first == 0) break;
                action p = { { pos,board[pos.second][pos.first] }, { np,c } };
                ret.emplace_back(p);
                break;
            }
        }
    }

    return ret;
}

va pawnmove(p2 pos, bool white)
{
    if (pos.second == 7 || pos.second == 0)
    {
        va ret = movedir(knight, pos, 1, white);
        va r = movedir(queen, pos, inf, white);
        repe(item, r) ret.emplace_back(item);
        return ret;
    }
    else
    {
        vp2 moves = { {0,1},{-1,1},{1,1} };

        if (white)
        {
            repe(m, moves)
            {
                m.first *= -1;
                m.second *= -1;
            }
        }

        va ret = movedir(moves, pos, 1, white, true);

        if ((white && pos.second == 6) || (!white && pos.second == 1))
        {
            moves = { {0,1} };
            if (white)
            {
                repe(m, moves)
                {
                    m.first *= -1;
                    m.second *= -1;
                }
            }
            va r2 = movedir(moves, pos, 2, white, true);
            repe(m, r2) ret.emplace_back(m);
        }

        return ret;
    }
}

va getmoves(p2 pos, bool white)
{
    char piece = board[pos.second][pos.first];
    switch (piece)
    {
    case 'n':
    case 'N':
        return movedir(knight, pos, 1, white);
    case 'B':
    case 'b':
        return movedir(diagonal, pos, inf, white);
    case 'R':
    case 'r':
        return movedir(cross, pos, inf, white);
    case 'K':
    case 'k':
        return movedir(queen, pos, 1, white);
    case 'Q':
    case 'q':
        return movedir(queen, pos, inf, white);
    case 'P':
    case 'p':
        return pawnmove(pos, white);
    default:
        return {};
        break;
    }
}


va getallmoves(bool white)
{
    vi& col = white ? is_white : is_black;

    va ret;

    rep(i, 8) rep(j, 8)
    {
        if (col[board[j][i]])
        {

            va moves = getmoves({ i,j }, white);

            repe(mov, moves) ret.emplace_back(mov);
        }
    }

    return ret;
}

bool in_check(bool white)
{
    repe(move, getallmoves(!white))
    {
        if (toupper(board[move.to.first.second][move.to.first.first]) == 'K')
        {
            return true;
        }
    }

    return false;
}

bool is_mate()
{
    if (!in_check(false)) return false;

    repe(move, getallmoves(false))
    {
        domove(move.from.first, move.to.first);
        bool mated = in_check(false);
        undomove();
        if (!mated) return false;
    }

    return true;
}

string actiontonotation(action a)
{
    string ret = "";
    ret += string(1, a.from.first.first + 'a');
    ret += string(1, 8 - a.from.first.second + '0');
    ret += string(1, a.to.first.first + 'a');
    ret += string(1, 8 - a.to.first.second + '0');
    return ret;
}

int32_t main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\desktop\\kryssring\\attachments\\5.in");
#endif

    repe(c, "PNBRQK")
    {
        is_white[c] = true;
    }

    repe(c, "pnbrqk")
    {
        is_black[c] = true;
    }


    board = vector<string>(8);
    rep(i, 8) read(board[i]);
    vector<string> c(board);


    repe(move, getallmoves(true))
    {
        domove(move.from.first, move.to.first);
        if (!in_check(true) && is_mate())
        {
            cout << actiontonotation(move);
            quit;
        }
        undomove();
        debassert(c == board);
    }

    quit;
}
