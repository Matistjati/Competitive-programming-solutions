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

// Global variables make heuristic problems a lot easier
int bestScore = 0;
string bestNew;
string bestSequence;
p2 bestPos;

int w;
int h;

// Kill any branches where the robot gets stuck
const int illegalPenalty = 100;

map<char, p2> directions = { {'>',{1,0}},{'<',{-1,0}},{'v',{0,1}},{'^',{0,-1}} };
map<char, vector<char>> newDirection = { {'>',{'v','^','<'}}, {'<',{'v','^','>'}},{'v',{'>','^','<'}},{'^',{'v','>','<'}} };
vector<char> allDirections = { '>','<','v','^' };

// A vector for each depth to copy the grid
vector<vector<bool>> copys;

// Move the robot in a direction. Keeps track of what we've cleaned and gets a huge penalty if we enter an area which is a dead end, killing the branch
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

// Do a depth-limited search and select the locally best path
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

// Move without cleaning anything. Useful for the BFS functions
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


// BFS down to the bottom
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

// Use BFS to find a column to go down. Extremely unoptimized, but it runs in ~0.3s, so who cares
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

    // True for no wall
    bitmap grid = bitmap(h, vector<bool>(w, true));
    bitmap illegal = bitmap(h, vector<bool>(w));

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


    // Depth optimization
    //                     0  1  2  3  4  5  6  7  8  9  10
    vector<int> depths = { 10,10,9, 13,11,11,11,10,10,11,9 };
    int depth = depths[t];
    //if (t != 4)
    //{
    //    quit;
    //}

    // For each depth, we want to make a copy of the column/row that is going to be modified.
    // In order to increase performance, we can reuse these
    copys = vector<vector<bool>>(depth + 2, vector<bool>(w));
    bestNew.reserve(depth*2);

    if (t==10)
    {
        // BFS down to the bottom of the grid
        pair<p2, string> m = bfsdown(grid, startPos);

        startPos = m.first;
        n -= m.second.size();
        bestSequence += m.second;

        repe(c, m.second)
        {
            move(grid, illegal, cleaned, startPos, c, 0);
        }

        // There will be lots of gaps where we can go down, up again, then down, gaining 1000 score each time.
        // Do this until we can't anymore, without doing the same column twice.
        set<int> takenCols;
        takenCols.insert(1);
        while (bestSequence.size() < origN)
        {
            string nextSeq = bfsfind(grid, takenCols, startPos);
            repe(c, nextSeq)
            {
                move(grid, illegal, cleaned, startPos, c, 0);
            }
            bestSequence += nextSeq;
        }

        bestSequence = bestSequence.substr(0, origN);
        cout << bestSequence;
        quit;
    }


    int prevScore = 0;
    while (n)
    {
        // Do a depth-limited search and select the one with the best score
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

        // If we didn't increase our score, we're "stuck". Thus we backtrack a couple of steps and then mark the area as illegal.
        // This will make the robot lose alot of score when going into illegal areas, thus it won't become stuck again
        if (prevScore == cleaned.second)
        {
            illegal[startPos.second][startPos.first] = true;
            illegal[beginPos.second][beginPos.first] = true;

            // Reset our board
            cleaned = mp(vector<vector<bool>>(h, vector<bool>(w)), 0);
            // Undo a couple of steps
            bestSequence = bestSequence.substr(0, max(0, (int)(bestSequence.size() - float(depth * 2.8))));
            n = origN - bestSequence.size();

            startPos = origPos;
            repe(c, bestSequence)
            {
                move(grid, illegal, cleaned, startPos, c, 0);
            }
        }
        else
        {
            prevScore = cleaned.second;
        }
        bestNew = "";
    }

    cout << bestSequence;


    quit;
}
