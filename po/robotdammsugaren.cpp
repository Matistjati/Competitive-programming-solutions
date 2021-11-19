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
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))


inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif


    int r;
    int c;
    int n;
    read(r);
    read(c);
    read(n);

    string sequence;
    read(sequence);

    repe(c, sequence)
    {
        switch (c)
        {
        case '>':
            c = 0;
            break;
        case '<':
            c = 1;
            break;
        case '^':
            c = 2;
            break;
        case 'v':
            c = 3;
        default:
            break;
        }
    }

    vector<string> area(r);

    rep(i, r)
    {
        string s;
        read(s);
        area[i] = s;
    }

    pair<int, int> startPos;
    vector<vector<bool>> sweeped(r, vector<bool>(c, false));

    rep(row, r)
    {
        rep(column, c)
        {
            if (area[row][column] == 'O')
            {
                startPos = { row,column };
            }
            area[row][column] = area[row][column] == '#' ? 1 : 0;
        }
    }
breakout:;
    vector<pair<int, int>> directions = {{0,1},{0,-1},{-1,0},{1,0} };


    int sweepSum = 0;
    repe(command, sequence)
    {
        int xDir = directions[command].first;
        int yDir = directions[command].second;
        int d = 0;
        while (true)
        {
            if (!sweeped[startPos.first][startPos.second])
            {
                sweeped[startPos.first][startPos.second] = true;
                sweepSum++;
            }
            startPos.first += xDir;
            startPos.second += yDir;
            if (area[startPos.first][startPos.second])
            {
                startPos.first -= xDir;
                startPos.second -= yDir;
                break;
            }

            d++;
        }
    }

    write(sweepSum);

    return 0;
}