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

struct cell
{
    bool top;
    bool bottom;
    bool left;
    bool right;
};

#define movestate tuple<p2, bool, string>

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread3(int, w, h, n);

    vector<vector<cell>> grid(h+1, vector<cell>(w+1));

    rep(i, n)
    {
        dread4(int, x1, y1, x2, y2);
        if (x1==x2)
        {
            if (y1 > y2) swap(y1, y2);


            repp(j, y1, y2)
            {
                if (x1-1>=0)
                {
                    grid[j][x1 - 1].right = true;
                }
                grid[j][x1].left = true;
            }
        }
        else
        {
            if (x1 > x2) swap(x1, x2);


            repp(j, x1, x2)
            {
                if (y1 - 1 >= 0)
                {
                    grid[y1-1][j].bottom = true;
                }
                grid[y1][j].top = true;
            }
        }
    }

    queue<movestate> toDo;
    toDo.push({ {0,0}, true, ""});
    vector < vector<vector<bool>>> visited(h+1, vector<vector<bool>>(w+1, vector<bool>(2)));

    vector<pair<p2, char>> directions = { {{1,0},'H'},{{-1,0},'V'} };

    while (toDo.size())
    {
        p2 pos;
        bool down;
        string moves;
        tie(pos, down, moves) = toDo.front();
        toDo.pop();



        if (pos.first == w-1 && pos.second == h-1)
        {
            cout << moves;
            quit;
        }




        repe(dir, directions)
        {
            p2 newPos = pos;
            string newMove = moves;
            newMove += dir.second;


            if (dir.second == 'H' && grid[newPos.second][newPos.first].right)
            {
                continue;
            }
            if (dir.second == 'V' && grid[newPos.second][newPos.first].left)
            {
                continue;
            }


            newPos.first += dir.first.first;
            newPos.second += dir.first.second;
            if (!within(newPos.first, w + 1, newPos.second, h + 1))
            {
                continue;
            }

            p2 fallDirection = (down) ? mp(0, -1) : mp(0, 1);

            while (true)
            {
                if (down && grid[newPos.second][newPos.first].top)
                {
                    break;
                }
                else if (!down && grid[newPos.second][newPos.first].bottom)
                {
                    break;
                }

                newPos.first += fallDirection.first;
                newPos.second += fallDirection.second;
                if (!within(newPos.first, w + 1, newPos.second, h + 1))
                {
                    goto impossible2;
                }
            }

            if (!visited[newPos.second][newPos.first][down])
            {
                toDo.push({ newPos, down, newMove });
                visited[newPos.second][newPos.first][down] = true;
            }
        impossible2:;
        }

        {
            p2 newPos = pos;
            bool dir = !down;
            string newMove = moves;
            newMove += 'G';

            p2 direction = (dir) ? mp(0, -1) : mp(0, 1);
            while (true)
            {
                if (dir && grid[newPos.second][newPos.first].top)
                {
                    break;
                }
                else if (!dir && grid[newPos.second][newPos.first].bottom)
                {
                    break;
                }

                newPos.first += direction.first;
                newPos.second += direction.second;
                if (!within(newPos.first, w + 1, newPos.second, h + 1))
                {
                    goto impossible;
                }
            }

            if (!visited[newPos.second][newPos.first][dir])
            {
                toDo.push({ newPos, dir, newMove });
                visited[newPos.second][newPos.first][dir] = true;
            }


        }

    impossible:;

    }

    cout << "Inte";

    quit;
}