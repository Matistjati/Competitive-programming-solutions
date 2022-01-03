#include <bits/stdc++.h>
#include <bits/extc++.h>

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
#define vvvvi vector<vvvi>
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

using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

vvi adjacent;

struct UF
{
    vector<Tree<int>> angryCon;
    vector<Tree<int>> components;
    vb taken;
    vi parent;


    UF(int n) : angryCon(n), taken(n), parent(n), components(n)
    {
        rep(i, n)
        {
            parent[i] = i;
            components[i].insert(i);
        }
    }

    int find(int n) { return parent[n] == n ? n : parent[n] = find(parent[n]); };

    void merge(int a, int b)
    {
        parent[a] = b;
    }

    void add(int n)
    {
        bool found = false;

        repe(adj, adjacent[n])
        {
            if (taken[adj])
            {
                merge(n, adj);

                int group = find(adj);

                repe(ne, angryCon[n])
                {
                    angryCon[group].insert(ne);
                }

                angryCon[group].erase(-n);
                angryCon[group].erase(-adj);

                components[group].insert(n);

                break;
            }
        }
        taken[n] = true;
    }
};



int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Release\\in.txt");
#endif

    dread3(int, n, m, k);

    adjacent = vvi(n);

    rep(i, m)
    {
        dread2(int, a, b);
        a--;
        b--;
        adjacent[a].emplace_back(b);
        adjacent[b].emplace_back(a);
    }

    rep(i, n-k)
    {
        bool bad = false;
        repe(adj, adjacent[i])
        {
            if (adj >= n - k)
            {
                bad = true;
                break;
            }
        }

        if (!bad)
        {
            cout << "1\n" << (i + 1);
            quit;
        }
    }

    UF uf(n);
    rep(i, n)
    {
        repe(adj, adjacent[i])
        {
            uf.angryCon[i].insert(-adj);
        }
    }

    perr(i, n-k-1, n - 1)
    {
        uf.add(i);

        int group = uf.find(i);

        int largest = -first(uf.angryCon[group]);


        auto it = uf.components[group].lower_bound(largest);
        int blocking = 0;
        if (it != uf.components[group].end())
        {
            blocking = uf.components[group].size() - uf.components[group].order_of_key(*it);
        }

        int lowest = n-k-blocking;

        if (lowest > largest)
        {
            int root = uf.find(i);

            int size = 0;
            rep(j, n)
            {
                if (uf.find(j) == root)
                {
                    size++;
                }
            }
            cout << size << "\n";
            rep(j, n)
            {
                if (uf.find(j) == root)
                {
                    cout << j + 1 << " ";
                }
            }
            quit;
        }
    }

    write(-1);

    quit;
}
