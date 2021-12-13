#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define enablell 1

#define ll long long
#if enablell
#define int ll
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vp3 vector<p3>
#if enablell
#define inf 1e18
#else
#define inf int(1e9)
#endif

#define read(a) cin >> a
#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repp(i, low, high) for (ll i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)
#define perr(i, low, high) for (ll i = high; i >= low; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

#define bitmap vector<vector<bool>>
#define cleanmap pair<bitmap,int>


int bestScore = 0;
string bestNew;
string bestSequence;

int w;
int h;


map<char, p2> directions = { {'>',{1,0}},{'<',{-1,0}},{'v',{0,1}},{'^',{0,-1}} };
map<char, vector<char>> newDirection = { {'>',{'v','^','<'}}, {'<',{'v','^','>'}},{'v',{'>','^','<'}},{'^',{'v','>','<'}} };
vector<char> allDirections = { '>','<','v','^' };


inline pair<p2, vector<bool>> move(bitmap& grid, cleanmap& cleaned, p2& pos, char dir)
{
    pair<p2, vector<bool>> ret = { {(dir == '<' || dir == '>') ? pos.first : pos.second,-1},{cleaned.first[pos.second][pos.first]} };
    ret.second.reserve(w);

    switch (dir)
    {
    case '>':
        while (true)
        {
            pos.first++;


            if (!grid[pos.second][pos.first])
            {
                pos.first--;
                ret.first.second = pos.first;
                if (ret.first.first > ret.first.second) swap(ret.first.first, ret.first.second);
                ret.first.second++;
                return ret;
            }

            ret.second.emplace_back(cleaned.first[pos.second][pos.first]);
            if (!cleaned.first[pos.second][pos.first])
            {
                cleaned.first[pos.second][pos.first] = true;
                cleaned.second++;
            }
        }
    case '<':
        while (true)
        {
            pos.first--;

            if (!grid[pos.second][pos.first])
            {
                pos.first++;
                ret.first.second = pos.first;
                if (ret.first.first > ret.first.second) swap(ret.first.first, ret.first.second);
                reverse(all(ret.second));
                ret.first.second++;
                return ret;
            }

            ret.second.emplace_back(cleaned.first[pos.second][pos.first]);
            if (!cleaned.first[pos.second][pos.first])
            {
                cleaned.first[pos.second][pos.first] = true;
                cleaned.second++;
            }
        }
    case 'v':
        while (true)
        {
            pos.second++;

            if (!grid[pos.second][pos.first])
            {
                pos.second--;
                ret.first.second = pos.second;
                if (ret.first.first > ret.first.second) swap(ret.first.first, ret.first.second);
                ret.first.second++;
                return ret;
            }

            ret.second.emplace_back(cleaned.first[pos.second][pos.first]);
            if (!cleaned.first[pos.second][pos.first])
            {
                cleaned.first[pos.second][pos.first] = true;
                cleaned.second++;
            }
        }
    case '^':
        while (true)
        {
            pos.second--;

            if (!grid[pos.second][pos.first])
            {
                pos.second++;
                ret.first.second = pos.second;
                if (ret.first.first > ret.first.second) swap(ret.first.first, ret.first.second);
                reverse(all(ret.second));
                ret.first.second++;
                return ret;
            }

            ret.second.emplace_back(cleaned.first[pos.second][pos.first]);
            if (!cleaned.first[pos.second][pos.first])
            {
                cleaned.first[pos.second][pos.first] = true;
                cleaned.second++;
            }
        }
    default:
        break;
    }


}


uniform_int_distribution<int> dist(0, 1);
mt19937 rng(69);

void printgrid(cleanmap& cleaned)
{
    int k = 0;
    repe(row, cleaned.first)
    {
        rep(i, row.size())
        {
            k += row[i];
            cout << (row[i] ? '#' : '.');
        }
        write("");
    }
    write(k);
}

void printgridplayer(cleanmap& cleaned, p2& pos)
{
    int k = 0;
    rep(j, cleaned.first.size())
    {
        vector<bool>& row = cleaned.first[j];
        rep(i, row.size())
        {
            k += row[i];
            if (j==pos.second&&i==pos.first)
            {
                cout << 'O';
            }
            else
            {
                cout << (row[i] ? '#' : '.');
            }
        }
        write("");
    }
    write(k);
}


void printgridplayer2(bitmap& cleaned, p2& pos)
{
    int k = 0;
    rep(j, cleaned.size())
    {
        vector<bool>& row = cleaned[j];
        rep(i, row.size())
        {
            k += row[i];
            if (j == pos.second && i == pos.first)
            {
                cout << 'O';
            }
            else
            {
                cout << (row[i] ? '.' : '#');
            }
        }
        write("");
    }
    write(k);
}


void dls(bitmap& grid, cleanmap& cleaned, p2 pos, char dir, int depth, string& seq)
{

    if (depth < 0)
    {
        if (cleaned.second > bestScore || (cleaned.second == bestScore && dist(rng)))
        {
            bestScore = cleaned.second;
            bestNew = seq;
        }

        return;
    }

    if (dir != '-')
    {
        int oldScore = cleaned.second;
        pair<p2,vector<bool>> c = move(grid, cleaned, pos, dir);

        if (depth==0)
        {
            dls(grid, cleaned, pos, '-', depth - 1, seq);
        }
        else
        {
            repe(newDir, newDirection[dir])
            {
                seq += newDir;
                dls(grid, cleaned, pos, newDir, depth - 1, seq);
                seq.pop_back();
            }
        }


        if (dir == '>' || dir == '<')
        {
            //cleaned.first[pos.second] = copy;
            repp(i, c.first.first, c.first.second)
            {
                cleaned.first[pos.second][i] = c.second[i - c.first.first];
            }
        }
        else
        {
            repp(i, c.first.first, c.first.second)
            {
                cleaned.first[i][pos.first] = c.second[i - c.first.first];
            }
        }
        cleaned.second = oldScore;
    }
    else
    {
        repe(newDir, allDirections)
        {
            seq += newDir;
            dls(grid, cleaned, pos, newDir, depth - 1, seq);
            seq.pop_back();
        }
    }
}


int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread(int, t);
    read(h);
    read(w);
    dread(int, n);

    readvector(string, area, h);

    cleanmap cleaned = mp(vector<vector<bool>>(h, vector<bool>(w)), 0);

    bitmap grid = bitmap(h, vector<bool>(w, true));

    bestSequence = "";
    bestSequence.reserve(n);

    p2 startPos = { -1,-1 };

    rep(i, h)
    {
        rep(j, w)
        {
            if (area[i][j] == '#')
            {
                grid[i][j] = false;
            }
            else if (area[i][j] == 'O')
            {
                cleaned.first[i][j] = true;
                startPos = { j,i };
            }
        }
    }
    p2 origPos = startPos;


    //                     0  1  2  3  4  5  6  7  8  9  10
    vector<int> depths = { 1,18,10,10,10,10,10,10,8, 8, 8,10,10,10,10 };
    int depth = depths[t];
    if (t != 3)
    {
        quit;
    }

    /*cleaned.first[startPos.second + 2][startPos.first] = true;
    printgrid(cleaned);
    pair<p2,vector<bool>> c = move(grid, cleaned,startPos, '^');

    repp(i, c.first.first, c.first.second)
    {
        cleaned.first[startPos.second][i] = c.second[i - c.first.first];
    }

    repp(i, c.first.first, c.first.second)
    {
        cleaned.first[i][startPos.first] = c.second[i - c.first.first];
    }

    printgrid(cleaned);
    deb*/
    printgridplayer(cleaned, startPos);

    while (n)
    {
        bestScore = -inf;
        string newSeq;
        dls(grid, cleaned, startPos, '-', min(depth, n), newSeq);
        n -= bestNew.size();
        bestSequence += bestNew;
        p2 beginPos = startPos;

        repe(c, bestNew)
        {
            move(grid, cleaned, startPos, c);
        }
        //printgridplayer(cleaned, beginPos);
        printgridplayer(cleaned, beginPos);
        printgridplayer2(grid, beginPos);
        bestNew = "";
    }

    printgrid(cleaned);
    cout << bestSequence;

    quit;
}
