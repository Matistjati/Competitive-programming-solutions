#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>


#ifdef GNEGN
#include <bits/extc++.h>
using namespace __gnu_pbds;
#endif

using namespace std;

#define enablell 1

#define ll long long
#if enablell
#define int ll
#define inf (int)(2e18)
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
#define read3(a,b,c) cin >> a >> b >> c
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
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

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
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s);  string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }

int n, k;


p2 ans(vvp2& edges, vvp2& dp, bool matched, int curr, int parent, int cost)
{
    p2& v = dp[curr][matched];
    if (v.first != -1) return v;
    //p2 v = { 0,0 };

    vp2 match1;
    vp2 match2;

    p2 ret = { 0,0 };

    int availableOnes = 0;

    repe(edge, edges[curr])
    {
        if (edge.first == parent) continue;

        p2 a = ans(edges, dp, false, edge.first, curr, 0);
        p2 b = ans(edges, dp, true, edge.first, curr, edge.second);
        match1.emplace_back(a);
        match2.emplace_back(b);
    }

    priority_queue<p2> optionalchanges;
    priority_queue<p2> obligatorychanges;
    rep(i, match1.size())
    {
        p2 m = match1[i];

        int c = 0;
        if (get<0>(m) != 0)
        {
            ret.first += m.first;
            cost += m.second;
        }

        if (match2[i].first + 1 == match1[i].first)
        {
            optionalchanges.emplace((match1[i].second - match2[i].second), i);
        }

        if (match2[i].first == match1[i].first)
        {
            obligatorychanges.emplace((match1[i].second-match2[i].second), i);
        }

    }

    int taken = matched;
    while (taken<k&&obligatorychanges.size())
    {
        p2 t = obligatorychanges.top();
        obligatorychanges.pop();
        if ((match1[t.second].first) != 0) cost -= match1[t.second].second;
        cost += match2[t.second].second;
        ret.first++;
        taken++;
    }

    while (taken < k && optionalchanges.size())
    {
        p2 t = optionalchanges.top();
        optionalchanges.pop();
        int newcost = cost;
        if ((match1[t.second].first) != 0) newcost -= match1[t.second].second;
        newcost += match2[t.second].second;
        if (newcost<cost)
        {
            if ((match1[t.second].first) != 0) cost -= match1[t.second].second;
            cost += match2[t.second].second;
            taken++;
        }

    }
    ret.second = cost;

    v = ret;

    return v;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Temp2\\Temp2\\in.txt");
#endif

    read2(n, k);


    vvp2 edges(n);
    bool allunit = true;
    rep(i, n - 1)
    {
        dread2(int, a, w);
        a--;
        if (w != 0)
        {
            allunit = false;
        }

        edges[a].emplace_back(i + 1, w);
        edges[i + 1].emplace_back(a, w);
    }

    if (true)
    {
        vvp2 dp(n, vp2(2, { -1,-1 }));

        p2 a = ans(edges, dp, false, 0, -1, 0);
        cout << a.first << " " << a.second;
    }
    else
    {
        cout << -1;
    }


    quit;
}