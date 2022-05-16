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
#define dread3(type, a, b, c) dread(type, a); dread(type, b); dread(type, c)
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) type temp; read(temp); a.push_back(temp);
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


    dread3(ll, n, m, t);

    int maxCoord = -1;
    queue<tuple<int, int,int>> toCheck;
    rep(i, n)
    {
        dread2(int, x, y);
        maxCoord = max(maxCoord, x);
        maxCoord = max(maxCoord, y);
        toCheck.push({ x,y,t });
    }
    set<pair<ll, ll>> chopped;
    rep(i, m)
    {
        dread2(ll, x, y);
        chopped.insert({ x,y });
    }

    if (n==1&&m==0)
    {
        ll ans = 2 * t * (t + 1) + 1;
        write(ans);
    }
    else if (t<401&&maxCoord<102)
    {
        set<pair<ll,ll>> visited;
        ll ans = 0;
        while (toCheck.size())
        {
            int x, y, left;
            tie(x,y,left) = toCheck.front();
            toCheck.pop();
            if (left < 0)
            {
                break;
            }
            pair<int, int> pos = { x,y};

            if (setcontains(visited, pos) || setcontains(chopped,pos))
            {
                continue;
            }
            else
            {
                ans++;
                visited.insert(pos);
            }

            vector<pair<int, int>> directions = { {0,1},{0,-1},{1,0},{-1,0} };
            repe(dir, directions)
            {
                toCheck.push({ x + dir.first,y + dir.second,left - 1 });
            }
        }
        write(ans);
    }
    else
    {
        write(-1);
    }

    _Exit(0);
}