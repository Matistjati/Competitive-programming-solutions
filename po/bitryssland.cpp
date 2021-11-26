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

    dread2(int, n, m);
    vector<ll> coins(n);
    vector<ll> value(n);
    rep(i, n)
    {
        dread(ll, amount);
        coins[i] = amount;
        value[i] = pow(2, i);
    }

    readvector(ll, toBuy, m);
    sort(all(toBuy));


    repe(cost, toBuy)
    {

        per(i, n - 1)
        {
            ll c = cost / value[i];
            if (c > coins[i])
            {
                cost -= coins[i] * value[i];
                coins[i] = 0;
            }
            else
            {
                coins[i] -= c;
                cost -= c * value[i];
            }
        }
        if (cost > 0)
        {
            cout << "nej" << endl;
            _Exit(0);
        }
    }

    cout << "ja" << endl;

    //return 0;
    _Exit(0);
}