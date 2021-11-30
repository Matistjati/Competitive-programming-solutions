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
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << endl
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


    dread(int, n);
    vector<tuple<int,int,int>> stations;
    vector<tuple<int,int,int>> profitableStations;
    rep(i, n)
    {
        dread2(int, enter, exit);
        if (enter-exit>0)
        {
            profitableStations.push_back({enter,exit,i});
        }
        else
        {
            stations.push_back({ enter, exit, i });
        }
    }

    sort(all(profitableStations), [](const ip3& lhs, const ip3& rhs)
        {
            return get<1>(lhs) < get<1>(rhs);
        });

    vector<int> order(n);
    int index = 0;
    int onTrain = 0;
    repe(station, profitableStations)
    {
        int enter, exit, i;
        tie(enter, exit, i) = station;

        if (exit<=onTrain)
        {
            onTrain -= exit;
        }
        else
        {
            cout << "NEJ" << endl;
            _Exit(0);
        }
        onTrain += enter;
        order[index] = i+1;
        index++;
    }

    sort(all(stations), [](const ip3& lhs, const ip3& rhs)
        {
            return get<0>(lhs) > get<0>(rhs);
        });


    repe(station, stations)
    {
        int enter, exit, i;
        tie(enter, exit, i) = station;

        if (exit <= onTrain)
        {
            onTrain -= exit;
        }
        else
        {
            cout << "NEJ" << endl;
            _Exit(0);
        }
        onTrain += enter;
        order[index] = i + 1;
        index++;
    }

    cout << "JA\n";
    rep(i, n)
    {
        cout << order[i] << " ";
    }
    cout << endl;

    //return 0;
    _Exit(0);
}