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

int cheapest(vi& dp, vi& visits, vi& durations, vi& prices, vi& jobdays, int index, int cost)
{
    if (index>=visits.size())
    {
        return cost;
    }

    int& v = dp[index];

    if (v != -1) return v + cost;

    int day = visits[index];
    int ret = inf;
    rep(i, durations.size())
    {
        auto it = lower_bound(all(visits), day + durations[i]);
        int newIndex = it != visits.end() ? (it - visits.begin()) : visits.size();
        if (newIndex <= index)
        {
            continue;
        }
        ret = min(ret, cheapest(dp,visits,durations,prices,jobdays, newIndex, cost+prices[i]));
    }


    if (jobdays.size())
    {
        auto it = lower_bound(all(jobdays), day);

        int jobDay = -1;

        if (it==jobdays.end())
        {
            jobDay = it != jobdays.begin() ? *prev(it) : inf;
        }
        else if (*it==day)
        {
            jobDay = day;
        }
        else
        {
            jobDay = it != jobdays.begin() ? *prev(it) : *it;
        }

        if (jobDay <= day)
        {
            rep(i, durations.size())
            {
                auto it = lower_bound(all(visits), jobDay + durations[i]);
                int newIndex = it != visits.end() ? (it - visits.begin()) : visits.size();
                if (newIndex <= index)
                {
                    continue;
                }
                ret = min(ret, cheapest(dp, visits, durations, prices, jobdays, newIndex, cost + prices[i] / 2));
            }
        }


    }


    v = ret - cost;

    return ret;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread3(int, n, m, k);

    readvector(int, visits, n);
    readvector(int, durations, m);
    readvector(int, prices, m);
    readvector(int, jobs, k);

    vi dp(n, -1);

    cout << cheapest(dp,visits,durations,prices,jobs,0,0);

    quit;
}