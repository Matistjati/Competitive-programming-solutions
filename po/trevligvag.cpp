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
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread(type, a); dread(type, b); dread(type, c)
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))


inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

inline bool possible(vector<vector<pair<ll,ll>>>& connections, double target)
{
    vector<double> best(connections.size(), -inf);
    best[0] = 0;

    rep(i, connections.size())
    {
        repe(con, connections[i])
        {
            best[con.first] = max(best[con.first], con.second+best[i]-target);
        }
    }

    return best[connections.size()-1] > 0;
}

int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread2(ll, n, m);
    vector<vector<pair<ll, ll>>> connections(n);
    rep(i, m)
    {
        dread3(ll, a, b, value);
        a--;
        b--;
        connections[min(a, b)].push_back({ max(a,b),value });
    }

    double low = 0;
    double high = linf;
    rep(i, 100)
    {
        double mid = (low + high) / 2;

        if (possible(connections, mid))
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
        if (high-low<1e-7)
        {
            break;
        }
    }


    cout << fixed << setprecision(15) << low;

    return 0;
    //_Exit(0);
}