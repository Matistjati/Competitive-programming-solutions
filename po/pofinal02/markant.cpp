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
#define vb vector<bool>
#define vvb vector<vb>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vp3 vector<p3>
#define vp4 vector<p4>
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
#define noop cout << "";
#define deb __debugbreak();
#else
#define noop ;
#define deb ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high; i >= 0; i--)
#define perr(i, low, high) for (int i = high; i >= low; i--)

#define readpush(type,vect) type temp; read(temp); vect.(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define insideinterval(v, interval) (v >= interval.first && v <= interval.second)
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


struct cell
{
    bool up;
    bool down;
    bool right;
    bool left;
};

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread3(int, w, h, n);


    set<int> sxCoords;
    set<int> syCoords;
    queue<pair<p2,p2>> lines;

    rep(i, n)
    {
        dread4(int, x1, y1, x2, y2);

        if (y1 > y2) swap(y1, y2);
        if (x1 > x2) swap(x1, x2);
        lines.emplace(mp(x1, y1), mp(x2, y2));
        sxCoords.insert(x1);
        sxCoords.insert(x2);
        syCoords.insert(y1);
        syCoords.insert(y2);


    }

    vi xCoords(all(sxCoords));
    vi yCoords(all(syCoords));

    vector<vector<cell>> adjacent(yCoords.size(), vector<cell>(xCoords.size()));

    while (lines.size())
    {
        pair<p2,p2> s = lines.front();
        lines.pop();


        int x1 = find(all(xCoords), s.first.first) - xCoords.begin();
        int x2 = find(all(xCoords), s.second.first) - xCoords.begin();
        int y1 = find(all(yCoords), s.first.second) - yCoords.begin();
        int y2 = find(all(yCoords), s.second.second) - yCoords.begin();

        p2 d = (x1 == x2) ? mp(0, 1) : mp(1, 0);

        while (x1 < x2 || y1 < y2)
        {

            if (d.first)
            {
                adjacent[y1][x1].down = true;
                if (y1 - 1 >= 0)
                {
                    adjacent[y1-1][x1].up = true;
                }
            }
            else
            {
                adjacent[y1][x1].left = true;

                if (x1 - 1 >= 0)
                {

                    adjacent[y1][x1-1].right = true;
                }
            }

            x1 += d.first;
            y1 += d.second;
        }
    }

    int ans = -inf;
    vvb visited(101, vb(101));
    queue<p2> toDo;

    rep(i, xCoords.size()-1)
    {
        rep(j, yCoords.size()-1)
        {
            toDo.emplace(i, j);
        }
    }

    while (toDo.size())
    {
        p2 start = toDo.front();
        toDo.pop();

        if (visited[start.first][start.second])
        {
            continue;
        }

        queue<p2> tocheck;
        tocheck.push(start);
        int area = 0;

        while (tocheck.size())
        {
            p2 curr = tocheck.front();
            tocheck.pop();

            if (visited[curr.first][curr.second])
            {
                continue;
            }

            visited[curr.first][curr.second] = true;

            set<p2> directions = {};
            if (!adjacent[curr.second][curr.first].right)
            {
                directions.insert(mp(1, 0));
            }
            if (!adjacent[curr.second][curr.first].left)
            {
                directions.insert(mp(-1, 0));
            }
            if (!adjacent[curr.second][curr.first].up)
            {
                directions.insert(mp(0, 1));
            }
            if (!adjacent[curr.second][curr.first].down)
            {
                directions.insert(mp(0, -1));
            }


            area += (xCoords[curr.first+1] - xCoords[curr.first]) * (yCoords[curr.second+1] - yCoords[curr.second]);

            repe(dir, directions)
            {
                p2 p = curr;
                p.first += dir.first;
                p.second += dir.second;
                tocheck.emplace(p);
            }
        }

        ans = max(ans, area);

    }



    cout << ans;

    quit;
}
