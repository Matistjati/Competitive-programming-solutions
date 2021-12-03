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
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

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
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif


    dread2(int, n, p);
    vector<int> distancePrefix(n);
    vector<int> distances(n);
    for (int i = 1; i < n; i++)
    {
        dread(int, d);
        distancePrefix[i] = distancePrefix[i-1]+d;
        distances[i] = d;
    }

    vector<ip4> passengers(p);
    rep(i, p)
    {
        dread3(int, start, end, max);
        passengers[i] = { start,end,max, distancePrefix[end-1]- distancePrefix[start-1]};
    }

    int ans = -inf;
    int shortestEndTime = inf;
    vector<int> bestTimeTable;
    int tableMask;
    rep(i, 1 << (n - 2))
    {
        int mask = i << 2;
        mask |= 2;
        mask |= (1 << (n));

        vector<int> timeTravelled(n+1);
        vector<int> totTime(n+1);
        for (int i = 1; i < n+1; i++)
        {
            if (mask & (1 << i))
            {
                timeTravelled[i]++;
                if (i+1<n+1)
                {

                    timeTravelled[i + 1]++;
                }
            }
            timeTravelled[i] += distances[i-1] / 2;

        }
        timeTravelled[1]--;
        for (int i = 1; i < n+1; i++)
        {
            totTime[i] = totTime[i - 1] + timeTravelled[i];
        }

        int tot = 0;
        repe(passenger, passengers)
        {
            if (mask & (1<<get<0>(passenger)) && mask & (1<<get<1>(passenger)))
            {
                if (totTime[get<1>(passenger)]-totTime[get<0>(passenger)] <= get<2>(passenger))
                {
                    tot += get<3>(passenger);
                }
            }
        }

        if (tot > ans || (tot == ans && totTime[n-1] < shortestEndTime))
        {
            ans = tot;
            tableMask = mask;
            bestTimeTable = totTime;
            shortestEndTime = totTime[n-1];
        }
    }


    write(ans);
    rep(i, bestTimeTable.size())
    {
        if (tableMask & (1 << (i+1)))
        {
            cout << i+1 << " " << bestTimeTable[i+1] << "\n";
        }
    }

    cout << endl;
    _Exit(0);
}