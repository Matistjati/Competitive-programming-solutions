#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<int, int>
#define p3 tuple<ll,ll,ll>
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

    int r;
    int c;
    int k;
    read(r);
    read(c);
    read(k);

    vector<string> grid(r);
    vector<vector<int>> n_hits(r, vector<int>(c, inf));

    p2 start;
    p2 goal;
    rep(i, r)
    {
        dread(string, row);
        grid[i] = row;
        rep(j, row.size())
        {
            char c = row[j];
            if (c == 'S')
            {
                start = { i,j};
                row[j] = '.';
            }
            else if (c == 'G')
            {
                goal = { i,j };
                row[j] = '.';
            }
        }
    }

    queue<p3> toCheck;
    toCheck.push({ start.first,start.second,0 });

    vector<p2> directions = { {0,1},{0,-1},{1,0},{-1,0} };
    while (toCheck.size())
    {
        p3 curr = toCheck.front();
        toCheck.pop();

        if (get<0>(curr) == goal.first && get<1>(curr) == goal.second)
        {
            cout << (get<2>(curr)) << endl;
            _Exit(0);
        }

        repe(dir, directions)
        {
            for (int m = 1; m < k + 1; m++)
            {
                ll r1, c1, n;
                tie(r1, c1, n) = curr;
                r1 += dir.first * m;
                c1 += dir.second * m;

                if (c1 < 0 || c1 >= c || r1 < 0 || r1 >= r || grid[r1][c1] == '#' || n_hits[r1][c1] <= n)
                {
                    break;
                }
                if (n_hits[r1][c1] <= n + 1)
                {
                    continue;
                }

                n_hits[r1][c1] = n + 1;

                toCheck.push({ r1,c1,n + 1 });
            }
        }

    }


    cout << endl;
    _Exit(0);
}