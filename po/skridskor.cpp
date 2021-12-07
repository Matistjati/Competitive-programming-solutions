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

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, h, w);
    readvector(string, area, h);

    queue<pair<p2, p2>> toDo;
    toDo.push({ {0,0},{2,0} });
    vector<vector<vector<bool>>> visited(h+1, vector<vector<bool>>(w+1, vector<bool>(4)));

    vp2 directions = { {0,1},{0,-1},{1,0},{-1,0} };
    vp2 nextDirection = { {2,3},{2,3},{0,1},{0,1} };

    while (toDo.size())
    {
        p2 pos;
        p2 meta;
        tie(pos, meta) = toDo.front();
        toDo.pop();

        p2 nextDir = nextDirection[meta.first];

        repe(nextD, vector<ll>({ nextDir.first,nextDir.second }))
        {
            p2 newPos = pos;
            p2 dir = directions[nextD];
            while (true)
            {
                newPos.first += dir.first;
                newPos.second += dir.second;
                if (!within(newPos.first, h, newPos.second, w) || area[newPos.first][newPos.second] == '#')
                {
                    newPos.first -= dir.first;
                    newPos.second -= dir.second;
                    break;
                }
            }

            if (newPos.second == w - 1)
            {
                cout << meta.second << endl;
                _Exit(0);
            }

            if ((newPos.second == 0 && dir.second == -1) || (newPos.first == h - 1 && dir.first == 1) || (newPos.first == 0 && dir.first == -1))
            {
                continue;
            }

            if (!visited[newPos.first][newPos.second][nextD])
            {
                visited[newPos.first][newPos.second][nextD] = true;
                toDo.emplace(make_pair(newPos, make_pair(nextD, meta.second + 1)));
            }
        }
    }

    cout << endl;
    _Exit(0);
}