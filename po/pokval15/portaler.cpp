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
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
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

const int maxDepth = 17;

vvi parent;

int jump(int a, int d)
{
    if (d<=0)
    {
        return a;
    }
    for (int i = 0; i < maxDepth; i++) if (d & (1 << i))
        a = parent[a][i];
    return a;
}

#define UNVISITED -2

void findcycle(vb& seen, vi& incycle, queue<int>& cycles, int curr)
{
    if (seen[curr])
    {
        if (incycle[curr] == UNVISITED)
        {
            cycles.push(curr);
        }
        return;
    }
    seen[curr] = true;

    findcycle(seen, incycle, cycles, parent[curr][0]);
    incycle[curr] = 0;
}

int findlevels(vi& level, int curr)
{
    if (level[curr] != -1)
    {
        return level[curr] + 1;
    }

    return (level[curr] = findlevels(level, parent[curr][0])) + 1;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread(int, n);

    parent = vvi(n, vi(maxDepth));
    rep(i, n)
    {
        dread(int, next);
        next--;
        parent[i][0] = next;
    }
    repp(d, 1, maxDepth)
    {
        rep(i, n)
        {
            parent[i][d] = parent[parent[i][d - 1]][d - 1];
        }
    }


    dread(int, q);

    vb seen(n);
    queue<int> foundCycles;
    vi level(n,-1);

    vi incycle(n, UNVISITED);
    vi cycleOffset(n);
    int currcycle = 1;
    vvi cycles;

    rep(i, n)
    {
        if (!seen[i])
        {
            findcycle(seen, incycle, foundCycles, i);
        }
        while (foundCycles.size())
        {
            int start = foundCycles.front();
            foundCycles.pop();

            if (incycle[start])
            {
                continue;
            }

            vi cycle;

            int curr = start;
            int i = 0;

            do
            {
                cycle.emplace_back(curr);
                incycle[curr] = currcycle;
                cycleOffset[curr] = i;
                level[curr] = 0;
                curr = parent[curr][0];
                i++;
            } while (curr != start);

            cycles.emplace_back(cycle);

            currcycle++;
        }
    }

    rep(i, n)
    {
        findlevels(level, i);
    }

    rep(i, q)
    {
        dread2(int, a, b);
        a--;
        b--;

        if (!incycle[a] && !incycle[b])
        {
            int height = level[a] - level[b];
            cout << (jump(a, height) == b ? height : -1);
        }
        else if (incycle[a] && !incycle[b])
        {
            cout << -1;
        }
        else if (!incycle[a] && incycle[b])
        {
            int height = level[a];
            a = jump(a, height);
            if (incycle[a]==incycle[b])
            {
                if (cycleOffset[a] <= cycleOffset[b])
                {
                    cout << cycleOffset[b] - cycleOffset[a]+ height;
                }
                else
                {
                    cout << height + (cycleOffset[b]+(cycles[incycle[a]-1].size()-cycleOffset[a]));
                }
            }
            else
            {
                cout << -1;
            }
        }
        else if (incycle[a] && incycle[a] == incycle[b])
        {
            if (cycleOffset[a] < cycleOffset[b])
            {
                cout << cycleOffset[b] - cycleOffset[a];
            }
            else
            {
                cout << (cycleOffset[b] + (cycles[incycle[a] - 1].size() - cycleOffset[a]));
            }
        }
        else
        {
            cout << -1;
        }

        cout << "\n";
    }


    quit;
}
