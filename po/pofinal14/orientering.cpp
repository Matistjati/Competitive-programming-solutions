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



    dread4(int, h, w, px, py);
    px--;
    py--;
    p2 finish = { px,py };

    readvector(string, area, h);


    vector<vector<vector<int>>> visited(w, vector<vector<int>>(h, vector<int>(4, inf)));
    priority_queue<tuple<int, p2, char>> toDo;
    toDo.push({ 0,{0,0},'>' });

    vector<tuple<char, int, int>> directions = { {'^',-1,0},{'v',1,0},{'<',0,-1},{'>',0,1} };
    map<char, int> dirToIndex = { {'^',0},{'v',1},{'<',2},{'>',3} };
    map<char, p2> dirToDirection = { {'^',{-1,0}},{'v',{1,0}},{'<',{0,-1}},{'>',{0,1}} };

    while (toDo.size())
    {
        p2 pos;
        int n_ignored;
        char direction;
        tie(n_ignored, pos, direction) = toDo.top();
        n_ignored = -n_ignored;
        toDo.pop();

        if (pos == finish)
        {
            cout << n_ignored << endl;
            _Exit(0);
        }

        char intendedDirection = area[pos.first][pos.second];

        // Follow arrow
        if (intendedDirection != '.')
        {
            p2 dirToGo = dirToDirection[intendedDirection];
            p2 newPos = pos;
            newPos.first += dirToGo.first;
            newPos.second += dirToGo.second;
            if (within(newPos.first, h, newPos.second, w) && n_ignored < visited[newPos.second][newPos.first][dirToIndex[intendedDirection]])
            {
                visited[newPos.second][newPos.first][dirToIndex[intendedDirection]] = n_ignored;
                toDo.push({ -n_ignored, newPos, intendedDirection });
            }
        }

        p2 dirToGo = dirToDirection[direction];
        int n_new = n_ignored;
        if (direction != intendedDirection && intendedDirection != '.')
        {
            n_new++;
        }
        p2 newPos = pos;
        newPos.first += dirToGo.first;
        newPos.second += dirToGo.second;
        if (within(newPos.first, h, newPos.second, w) && n_ignored < visited[newPos.second][newPos.first][dirToIndex[direction]])
        {
            visited[newPos.second][newPos.first][dirToIndex[direction]] = n_ignored;
            toDo.push({ -n_new, newPos, direction });
        }
    }


    cout << endl;
    _Exit(0);
}