#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 tuple<ll,ll,ll>
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
#define repp(i, low, high) for (ll i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)

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
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    int n;
    int k;
    read(n);
    read(k);

    vector<int> series(k + 1);
    series[0] = (inf);
    for (int i = 1; i < k + 1; i++)
    {
        cin >> series[i];
    }


    vector<pair<int, vector<int>>> birthdays(n);
    rep(i, n)
    {
        int d;
        int c;
        read(d);
        read(c);

        vector<int> series(c);
        rep(j, c)
        {
            dread(int, s);
            series[j] = s;
        }
        birthdays[i] = { d,series };
    }

    sort(all(birthdays));

    int prev = 0;
    int savedHours = 0;
    rep(i, birthdays.size())
    {
        int hoursAvailable = (birthdays[i].first - prev) * 10 + savedHours;
        savedHours = 0;
        prev = birthdays[i].first + 1;

        vector<int>& daySeries = birthdays[i].second;
        rep(j, daySeries.size())
        {
            int seriesIndex = daySeries[j];
            if (series[seriesIndex] > 0)
            {
                if (hoursAvailable < series[seriesIndex])
                {
                    cout << "Nej" << endl;
                    _Exit(0);
                }
                else
                {
                    hoursAvailable -= series[seriesIndex];
                    series[seriesIndex] = 0;
                }
            }
        }

        if (hoursAvailable > 0)
        {
            savedHours = hoursAvailable;
        }
    }



    cout << "Ja";


    cout << endl;
    _Exit(0);
}