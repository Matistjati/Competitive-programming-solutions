#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define ip3 tuple<int,int,int>
#define ip4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << "\n"
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
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

#define board tuple<p2, p2,vector<string>>

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, h, w);
    vector<string> area(h);

    p2 playerPos;

    bool lying = false;
    p2 goal;

    rep(i, h)
    {
        dread(string, row);
        rep(j, row.size())
        {
            if (row[j]=='A')
            {
                playerPos = { i,j };
                row[j] = '.';
            }
            else if (row[j]=='B')
            {
                goal = { i,j };
                row[j] = '.';
            }
        }
        area[i] = (row);
    }



    queue<board> toDo;
    map<board, int> visited;
    toDo.push({ playerPos, playerPos, area });
    visited[{ playerPos, playerPos, area }] = 0;

    vp2 directions = { {0,1},{0,-1},{1,0},{-1,0} };
    while (toDo.size())
    {
        board curr = toDo.front();
        toDo.pop();

        int depth = visited[curr];

        vector<string> area;
        p2 pos;

        p2 secondPos;
        tie(pos, secondPos, area) = curr;

        bool lying = pos != secondPos;

        if (!lying && pos == goal)
        {
            cout << depth << endl;
            _Exit(0);
        }

        if (lying)
        {
            vp2 rollDirections = (pos.first-secondPos.first != 0) ? vp2({ {0, 1}, {0,-1} }) : vp2({ {1, 0}, {-1,0} });

            repe(dir, rollDirections)
            {
                p2 a = pos;
                a.first += dir.first;
                a.second += dir.second;
                p2 b = secondPos;
                b.first += dir.first;
                b.second += dir.second;
                if (within(a.first, h, a.second, w) && within(b.first, h, b.second, w) && area[a.first][a.second] != '#' && area[a.first][a.second] != '1'
                    && area[b.first][b.second] != '#' && area[b.first][b.second] != '1')
                {
                    board newState = { a, b, area };
                    if (!setcontains(visited, newState) || depth + 1 < visited[newState])
                    {
                        visited[newState] = depth + 1;
                        toDo.push(newState);
                    }
                }
            }

            vp2 block = { pos, secondPos};
            rep(i, 2)
            {
                p2 a = block[i];
                p2 b = block[(i + 1) % 2];
                p2 diff = { a.first - b.first, a.second - b.second };
                a = { a.first + diff.first, a.second + diff.second };
                if (within(a.first, h, a.second, w) && area[a.first][a.second] != '#' && area[a.first][a.second] != '1')
                {
                    vector<string> areaCopy(area);
                    if (areaCopy[a.first][a.second]=='c')
                    {
                        repe(row, areaCopy)
                        {
                            repe(g, row)
                            {
                                if (g=='0')
                                {
                                    g = '1';
                                }
                                else if (g == '1')
                                {
                                    g = '0';
                                }
                            }
                        }
                    }
                    board newState = { a, a, areaCopy };
                    if (!setcontains(visited, newState) || depth + 1 < visited[newState])
                    {
                        visited[newState] = depth + 1;
                        toDo.push(newState);
                    }
                }
            }
        }
        else
        {
            repe(dir, directions)
            {
                p2 a = pos;
                a.first += dir.first;
                a.second += dir.second;
                p2 b = a;
                b.first += dir.first;
                b.second += dir.second;
                if (within(a.first, h, a.second, w) && within(b.first, h, b.second, w) && area[a.first][a.second] != '#' && area[a.first][a.second] != '1'
                    && area[b.first][b.second] != '#' && area[b.first][b.second] != '1')
                {
                    board newState = { a, b, area };
                    if (!setcontains(visited,newState) || depth + 1 < visited[newState])
                    {
                        visited[newState] = depth + 1;
                        toDo.push(newState);
                    }
                }
            }
        }
    }

    cout << endl;
    _Exit(0);
}