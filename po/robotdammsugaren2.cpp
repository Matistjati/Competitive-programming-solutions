#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define enablell 0

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

template <typename T, typename U>
void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r)
{
    l = { l.first + r.first,l.second + r.second };
}

#define bitmap vector<vector<bool>>
#define cleanmap pair<bitmap,int>


int bestScore = 0;
string bestNew;
string bestSequence;
p2 bestPos;

int w;
int h;

const int illegalPenalty = 100;

map<char, p2> directions = { {'>',{1,0}},{'<',{-1,0}},{'v',{0,1}},{'^',{0,-1}} };
map<char, vector<char>> newDirection = { {'>',{'v','^','<'}}, {'<',{'v','^','>'}},{'v',{'>','^','<'}},{'^',{'v','>','<'}} };
vector<char> allDirections = { '>','<','v','^' };

vector<vector<bool>> copys;

inline pair<p2, vector<bool>&> move(bitmap& grid, bitmap& illegal, cleanmap& cleaned, p2& pos, char dir, int depth)
{
    pair<p2, vector<bool>&> ret = { {(dir == '<' || dir == '>') ? pos.first : pos.second,-1}, copys[depth]};
    ret.second[0] = (cleaned.first[pos.second][pos.first]);

    int i = 1;
    switch (dir)
    {
    case '>':
        while (true)
        {
            pos.first++;

            if (illegal[pos.second][pos.first])
            {
                cleaned.second -= illegalPenalty;
            }

            if (!grid[pos.second][pos.first])
            {
                pos.first--;
                ret.first.second = pos.first;
                if (ret.first.first > ret.first.second) swap(ret.first.first, ret.first.second);
                ret.first.second++;
                return ret;
            }

            ret.second[i] = cleaned.first[pos.second][pos.first];
            i++;
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

            if (illegal[pos.second][pos.first])
            {
                cleaned.second -= illegalPenalty;
            }

            if (!grid[pos.second][pos.first])
            {
                pos.first++;
                ret.first.second = pos.first;
                if (ret.first.first > ret.first.second) swap(ret.first.first, ret.first.second);
                reverse(begin(ret.second), begin(ret.second) + i);
                ret.first.second++;
                return ret;
            }

            ret.second[i] = cleaned.first[pos.second][pos.first];
            i++;
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

            if (illegal[pos.second][pos.first])
            {
                cleaned.second -= illegalPenalty;
            }

            if (!grid[pos.second][pos.first])
            {
                pos.second--;
                ret.first.second = pos.second;
                if (ret.first.first > ret.first.second) swap(ret.first.first, ret.first.second);
                ret.first.second++;
                return ret;
            }

            ret.second[i] = cleaned.first[pos.second][pos.first];
            i++;
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

            if (illegal[pos.second][pos.first])
            {
                cleaned.second -= illegalPenalty;
            }

            if (!grid[pos.second][pos.first])
            {
                pos.second++;
                ret.first.second = pos.second;
                if (ret.first.first > ret.first.second) swap(ret.first.first, ret.first.second);
                reverse(begin(ret.second), begin(ret.second)+i);
                ret.first.second++;
                return ret;
            }

            ret.second[i] = cleaned.first[pos.second][pos.first];
            i++;
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


void printgridplayer3(bitmap& grid, cleanmap& cleaned, p2& pos)
{
    int k = 0;
    rep(j, grid.size())
    {
        vector<bool>& rowG = grid[j];
        vector<bool>& rowC = cleaned.first[j];
        rep(i, rowG.size())
        {
            k += rowC[i];
            if (j == pos.second && i == pos.first)
            {
                cout << '_';
            }
            else
            {
                if (!rowG[i])
                {
                    cout << '#';
                }
                else if (rowC[i])
                {
                    cout << 'W';
                }
                else
                {
                    cout << '.';
                }
            }
        }
        write("");
    }
    write(k);
}

void printgridplayer4(bitmap& grid, cleanmap& cleaned, p2& pos, p2 x, p2 y)
{
    int k = 0;
    repp(j, y.first, y.second)
    {
        vector<bool>& rowG = grid[j];
        vector<bool>& rowC = cleaned.first[j];
        string rowV = "";
        repp(i, x.first, x.second)
        {
            k += rowC[i];
            if (j == pos.second && i == pos.first)
            {
                rowV += '_';
            }
            else
            {
                if (!rowG[i])
                {
                    rowV += '#';
                }
                else if (rowC[i])
                {
                    rowV += 'W';
                }
                else
                {
                    rowV += '.';
                }
            }
        }
        write(rowV);
    }
    write(k);
}


void printgridplayer5(bitmap& grid, p2& pos, p2 x, p2 y)
{
    int k = 0;
    repp(j, y.first, y.second)
    {
        vector<bool>& rowG = grid[j];
        string rowV = "";
        repp(i, x.first, x.second)
        {
            if (j == pos.second && i == pos.first)
            {
                rowV += '_';
            }
            else
            {
                if (!rowG[i])
                {
                    rowV += '#';
                }
                else
                {
                    rowV += '.';
                }
            }
        }
        write(rowV);
    }
    write(k);
}

int eval(cleanmap& cleaned)
{
    int k = 0;
    rep(j, cleaned.first.size())
    {
        vector<bool>& rowC = cleaned.first[j];
        rep(i, rowC.size())
        {
            k += rowC[i];
        }
    }
    return k;
}

uniform_int_distribution<int> dist(0, 2);
mt19937 rng(69);


void dls(bitmap& grid, bitmap& illegal, cleanmap& cleaned, p2 pos, char dir, int depth, string& seq)
{

    if (depth < 0)
    {
        if (cleaned.second > bestScore)
        {
            bestScore = cleaned.second;
            bestNew = seq;
            bestPos = pos;
        }

        return;
    }

    if (dir != '-')
    {
        int oldScore = cleaned.second;
        pair<p2, vector<bool>&> c = move(grid, illegal, cleaned, pos, dir, depth);

        if (depth == 0)
        {
            dls(grid, illegal, cleaned, pos, '-', depth - 1, seq);
        }
        else
        {
            repe(newDir, newDirection[dir])
            {
                seq += newDir;
                dls(grid, illegal, cleaned, pos, newDir, depth - 1, seq);
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
            dls(grid, illegal, cleaned, pos, newDir, depth - 1, seq);
            seq.pop_back();
        }
    }
}


inline void movenoclean(bitmap& grid, p2& pos, char dir)
{
    p2& direction = directions[dir];

    switch (dir)
    {
    case '>':
        while (true)
        {
            pos.first++;

            if (!grid[pos.second][pos.first])
            {
                pos.first--;
                return;
            }
        }
    case '<':
        while (true)
        {
            pos.first--;

            if (!grid[pos.second][pos.first])
            {
                pos.first++;
                return;
            }
        }
    case 'v':
        while (true)
        {
            pos.second++;

            if (!grid[pos.second][pos.first])
            {
                pos.second--;
                return;
            }
        }
    case '^':
        while (true)
        {
            pos.second--;

            if (!grid[pos.second][pos.first])
            {
                pos.second++;
                return;
            }
        }
    default:
        break;
    }


}

pair<p2, string> bfsdown(bitmap& grid, p2 startpos)
{
    bitmap visited = bitmap(h, vector<bool>(w));
    queue<pair<p2, string>> toDo;
    toDo.push(mp(startpos, ""));

    while (toDo.size())
    {
        p2 p;
        string seq;
        tie(p,seq) = toDo.front();
        toDo.pop();

        if (p.second==h-2)
        {
            return mp(p, seq);
        }

        if (visited[p.second][p.first])
        {
            continue;
        }
        else
        {
            visited[p.second][p.first] = true;
        }

        repe(dir, allDirections)
        {
            p2 pc = p;
            movenoclean(grid, pc, dir);
            toDo.emplace(mp(pc, seq + dir));
        }
    }
}

const int colLookHeight = 20;


string bfsfind(bitmap& grid, set<int>& takenCols, p2 startpos)
{
    bitmap visited = bitmap(h, vector<bool>(w));
    queue<pair<p2, string>> toDo;
    toDo.push(mp(startpos, ""));

    int k = 0;
    while (toDo.size())
    {
        k++;
        p2 p;
        string seq;
        tie(p, seq) = toDo.front();
        toDo.pop();



        if (visited[p.second][p.first])
        {
            continue;
        }
        else
        {
            visited[p.second][p.first] = true;
        }

        if (p.second > 900 && p.second < 1002 && !setcontains(takenCols, p.first))
        {
            //printgridplayer5(grid, p, { max(0,p.first - 20),min(w - 2,p.first + 40) }, { p.second - 20,min(w - 2,p.second + 50) });
            bool works = true;
            repp(i, 0, 102)
            {
                if (!grid[p.second + i][p.first])
                {
                    works = false;
                    break;
                }
                if (p.second + i > 1004)
                {
                    break;
                }
            }

            if (works)
            {
                takenCols.insert(p.first);
                if (seq[seq.size()-1] != '^' && seq[seq.size()-1] != 'v')
                {
                    seq += 'v';
                }
                return seq;
            }
        }

        repe(dir, allDirections)
        {
            p2 pc = p;
            movenoclean(grid, pc, dir);
            toDo.emplace(mp(pc, seq + dir));
        }
    }
    //cout << k;
    return "";
}



int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Release\\in.txt");
#endif

    dread(int, t);
    read(h);
    read(w);
    dread(int, n);
    int origN = n;

    readvector(string, area, h);

    cleanmap cleaned = mp(vector<vector<bool>>(h, vector<bool>(w)), 0);

    bitmap grid = bitmap(h, vector<bool>(w, true));
    bitmap illegal = bitmap(h, vector<bool>(w));

    bestSequence = "";
    bestSequence.reserve(n);

    p2 startPos = { -1,-1 };

    vp2 dirs = { {0,1},{0,-1},{1,0},{-1,0} };


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
    vector<int> depths = { 10,10,9, 13,12,11,11,10,10,11,9,10,10,10,10 };
    int depth = depths[t];
    /*if (t != 8)
    {
        quit;
    }*/
    copys = vector<vector<bool>>(depth + 2, vector<bool>(w));
    bestNew.reserve(depth*2);


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
    //printgridplayer(cleaned, startPos);

    //cout << eval(cleaned) << "\n";



    if (t==10)
    {
        pair<p2, string> m = bfsdown(grid, startPos);

        startPos = m.first;
        n -= m.second.size();
        bestSequence += m.second;
        //cout << m.second;
        repe(c, m.second)
        {
            move(grid, illegal, cleaned, startPos, c, 0);
        }

        /*move(grid, illegal, cleaned, startPos, '>', 0);
        move(grid, illegal, cleaned, startPos, '^', 0);
        printgridplayer4(grid, cleaned, startPos, { max(0,startPos.first - 20),min(w - 2,startPos.first + 40) }, { startPos.second - 20,min(w - 2,startPos.second + 50) });*/
        //cout << bestSequence;

        set<int> takenCols;
        takenCols.insert(1);
        while (bestSequence.size() < origN)
        {
            string nextSeq = bfsfind(grid, takenCols, startPos);
            repe(c, nextSeq)
            {
                move(grid, illegal, cleaned, startPos, c, 0);
                //printgridplayer4(grid, cleaned, startPos, { max(0,startPos.first - 20),min(w,startPos.first + 40) }, { startPos.second - 20,min(w,startPos.second + 50) });
            }
            bestSequence += nextSeq;
        }
        //
        //auto it = begin(seqsS);

        //vector<pair<int, string>> bestmoves;
        //vector<pair<int, string>> bestmoves2;


        //repe(seq, seqsS)
        //{
        //    //bestSequence += (*it);
        //    cleanmap before = cleaned;
        //    p2 pBef = startPos;
        //    int scoreBef = cleaned.second;
        //    repe(c, *it)
        //    {
        //        move(grid, illegal, cleaned, startPos, c, 0);
        //    }

        //    bestmoves.emplace_back(-((cleaned.second - scoreBef) / (int)(*it).size()), *it);

        //    cleaned = before;
        //    startPos = pBef;

        //    it = next(it);
        //}

        //sort(all(bestmoves));

        //repe(seq, bestmoves)
        //{
        //    if (seq.second.empty())
        //    {
        //        continue;
        //    }
        //    //bestSequence += (*it);
        //    int scoreBef = cleaned.second;
        //    repe(c, seq.second)
        //    {
        //        move(grid, illegal, cleaned, startPos, c, 0);
        //    }

        //    bestmoves2.emplace_back(-((cleaned.second - scoreBef) / (int)(seq.second).size()), seq.second);



        //}

        //sort(all(bestmoves2));

        //repe(m, bestmoves2)
        //{
        //
        //    bestSequence += m.second;
        //    if (bestSequence.size() > origN)
        //    {
        //        break;
        //    }

        //    repe(c, m.second)
        //    {
        //        move(grid, illegal, cleaned, startPos, c, 0);
        //        //printgridplayer4(grid, cleaned, startPos, { max(0,startPos.first - 20),min(w - 2,startPos.first + 40) }, { startPos.second - 20,min(w-2,startPos.second + 50) });
        //    }
        //}

        bestSequence = bestSequence.substr(0, origN);
        cout << bestSequence;
        quit;
    }



    int prevScore = 0;
    int n_illegals = 0;
    vector<p2> illegals;
    while (n)
    {
        //if (n-depth*2.5<0)
        //{
        //    repe(illegalb, illegals)
        //    {
        //        illegal[illegalb.second][illegalb.first] = false;
        //    }
        //}
        bestScore = -inf;
        string newSeq;
        dls(grid, illegal, cleaned, startPos, '-', min(depth, n), newSeq);
        n -= bestNew.size();
        bestSequence += bestNew;
        p2 beginPos = startPos;


        repe(c, bestNew)
        {
            move(grid, illegal, cleaned, startPos, c, 0);
        }


        /*if (cleaned.second == prevScore)
        {
            throw new runtime_error("");
        }
        else
        {
            prevScore = cleaned.second;
        }*/
        //printgridplayer(cleaned, beginPos);
        //printgridplayer3(grid, cleaned, startPos);
        if (prevScore == cleaned.second && t != 10)
        {
            n_illegals++;

            illegal[startPos.second][startPos.first] = true;
            illegal[beginPos.second][beginPos.first] = true;
            illegals.emplace_back(startPos);
            illegals.emplace_back(beginPos);
            cleaned = mp(vector<vector<bool>>(h, vector<bool>(w)), 0);
            bestSequence = bestSequence.substr(0, max(0, (int)(bestSequence.size() - float(depth * 2.8))));
            n = origN - bestSequence.size();

            startPos = origPos;
            repe(c, bestSequence)
            {
                move(grid, illegal, cleaned, startPos, c, 0);
            }
            //printgridplayer3(grid, cleaned, startPos);
        }
        else
        {
            prevScore = cleaned.second;
        }
        bestNew = "";
    }

    //printgridplayer3(grid, cleaned, startPos);
    //printgrid(cleaned);
    //cout << eval(cleaned) << "\n";
    //cout << n_illegals;

    //if (eval(cleaned) == 1652)
    //{
    //cout << eval(cleaned) << "\n";
    cout << bestSequence;
    //}
    //else
    //{
    //    throw new runtime_error("");
    //}


    return 0;
    //quit;
}
