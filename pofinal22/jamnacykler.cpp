#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

#define enablell 0

#define ll long long
#if enablell
#define int ll
#define inf 2e18
#define float double
#else
#define inf int(2e9)
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define p2 pair<int, int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vvvp2 vector<vvp2>
#define p3 tuple<int,int,int>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define p4 tuple<int,int,int,int>
#define vp4 vector<p4>

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
#define debassert(expr) if (!(expr)) deb;
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debassert(expr) ;
#define debif(expr) ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high; i >= 0; i--)
#define perr(i, low, high) for (int i = high; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define rununtil(time) if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s);  string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }

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

vi get_components(vvi& edges)
{
    UF uf(edges.size());

    vi components;

    rep(i, edges.size())
    {
        repe(edge, edges[i])
        {
            uf.join(i, edge);
        }
    }

    rep(i, edges.size())
    {
        if (uf.find(i) == i)
        {
            components.emplace_back(i);
        }
    }

    return components;
}

void shuffle_g(vvi& edges)
{
    rep(i, edges.size()) {
        if (edges[i].size() == 0) continue;
        rep(j, 10)
        {
            int a = rand() % edges[i].size(), b = rand() % edges[i].size();
            if (a == b) continue;
            swap(edges[i][a], edges[i][b]);
        }
    }
}

#define UNVISITED 0
#define PROCESSING 1
#define VISITED 2

int get_path(vvi& edges, vi& colors, vi& depths, vi& path, int curr, int parent, int depth)
{
    if (colors[curr]==PROCESSING)
    {
        if (depth%2==depths[curr]%2 && curr != parent)
        {
            cout << "YES\n";
            path.emplace_back(curr);
            return curr;
        }
        else
        {
            return -1;
        }
    }

    if (colors[curr] == VISITED) return -1;
    depths[curr] = depth;

    colors[curr] = PROCESSING;

    repe(edge, edges[curr])
    {
        if (edge == parent) continue;
        int r = get_path(edges, colors, depths, path, edge, curr, depth + 1);
        if (r == -2) return -2;
        if (r!=-1)
        {
            path.emplace_back(curr);
            return r == curr ? -2 : r;
        }
    }

    colors[curr] = VISITED;

    return -1;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, n, m);

    vvi edges(n);

    rep(i, m)
    {
        dread2(int, a, b);
        a--;
        b--;
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }


    vi components = get_components(edges);

    vi path;
    rep(i, 10)
    {
        vi depths(n);
        vi colors(n);
        repe(component, components)
        {
            if (get_path(edges, colors, depths, path, component, -1, 0)!=-1)
            {
                cout << path.size()-1 << "\n";
                rep(p, path.size()-1)
                {
                    cout << path[p]+1 << " ";
                }
                quit;
            }
        }
        shuffle_g(edges);
    }


    cout << "NO";

    quit;
}