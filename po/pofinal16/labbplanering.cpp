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
#define vvi vector<vi>
#define vvvi vector<vvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vp3 vector<p3>
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
#define deb __debugbreak();
#else
#define deb ;
#endif

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repp(i, low, high) for (ll i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)
#define perr(i, low, high) for (ll i = high; i >= low; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
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

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread(int, n);

    vector<queue<int>> groups(n);

    vp2 startTimes;
    startTimes.reserve(n);
    int maxM = -1;
    rep(i, n)
    {
        dread(int, m);
        maxM = max(maxM, m);
        rep(j, m)
        {
            dread(int, time);
            if (j == 0 && m > 1)
            {
                startTimes.emplace_back(mp(time, i));
            }

            groups[i].emplace(time);
        }
    }

    int ans = 0;
    int time = 0;
    sort(all(startTimes));
    vp2 c(startTimes);

    map<int, int> startMap;

    repp(i, 1, startTimes.size())
    {
        startTimes[i].first += startTimes[i - 1].first;
        startTimes[i - 1].first -= c[i - 1].first;
    }
    startTimes[startTimes.size() - 1].first -= c[startTimes.size() - 1].first;

    repe(s, startTimes)
    {
        startMap[s.second] = s.first;
    }


    priority_queue<p2> bestfinishing;


    rep(j, groups.size())
    {
        queue<int>& g = groups[j];
        if (g.size()==1)
        {
            ans += g.front();
            time += g.front();
            g.pop();
        }
        while (g.size())
        {
            if (g.size() > 1)
            {
                time += g.front();
            }
            else
            {
                bestfinishing.emplace(mp(g.front(),j));
            }
            g.pop();
        }
    }

    while (bestfinishing.size())
    {
        time += bestfinishing.top().first;
        ans += time-startMap[bestfinishing.top().second];
        bestfinishing.pop();
    }

    write(ans);

    quit;
}