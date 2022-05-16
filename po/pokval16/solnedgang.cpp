#include <bits/stdc++.h>
//#include <bits/extc++.h>

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
#define vvvb vector<vvb>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vvvp2 vector<vvp2>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define vp4 vector<p4>
#if enablell
#define inf 2e18
#else
#define inf int(2e9)
#endif

#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
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
#define debassert(expr) if (!(expr)) deb;

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
#define first(a) (*begin(a))

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


struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};


int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, n, k);


    map<int, vi> cols;
    map<p2, int> posToIndex;

    vp2 positions(n);

    rep(i, n)
    {
        dread2(int, x, y);

        positions[i] = { x,y + 1 };
        if (!setcontains(cols, x))
        {
            cols[x] = {};
        }
        cols[x].emplace_back(y);
        posToIndex[mp(x, y)] = i;
    }

    repe(col, cols)
    {
        sort(all(col.second));
    }

    queue<int> q;
    q.push(0);
    vb visited(n);

    vi offsets = { 1,-1 };

    priority_queue<p3> events;


    while (q.size())
    {
        int curr = q.front();
        q.pop();

        if (visited[curr])
        {
            continue;
        }
        visited[curr] = true;

        p2 p = positions[curr];

        auto above = upper_bound(all(cols[p.first]), p.second);
        int aboveHeight = above != cols[p.first].end() ? *above : inf;

        repe(offset, offsets)
        {
            if (setcontains(cols, p.first + offset))
            {
                vi& col = cols[p.first + offset];
                if (col.empty())
                {
                    continue;
                }

                auto start = upper_bound(all(col), p.second);
                auto ending = lower_bound(all(col), aboveHeight - 1);

                if (start != col.begin())
                {
                    start = prev(start);
                }





                for (; start < ending; start = next(start))
                {
                    int index = posToIndex[mp(p.first + offset, *start)];
                    ll t = abs(p.second-1-*start);
                    events.push({ -t, index, curr });
                    q.emplace(index);
                }
            }
        }

    }







    UF uf(n);
    if (n==1)
    {
        cout << 0;
        quit;
    }
    else
    {
        while (events.size())
        {
            ll t, a, b;
            tie(t, a, b) = events.top();
            events.pop();

            uf.join(a, b);

            if (uf.sameSet(0, n - 1))
            {
                t = (-t);
                cout << ((t < k) ? to_string(t) : "NATT");
                quit;
            }
        }
    }


    cout << "NATT";

    quit;
}