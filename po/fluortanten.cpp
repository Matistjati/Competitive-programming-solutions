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
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) type temp; read(temp); a.push_back(temp);
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


int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif



    dread(ll, n);
    vector<ll> queue(n);
    ll zeroIndex = -1;
    ll s = 0;
    rep(i, n)
    {
        dread(ll, happiness);
        s += happiness * (i + 1);
        if (happiness == 0)
        {
            zeroIndex = i;
        }
        queue[i] = happiness;
    }

    ll ans = s;

    ll s2 = s;
    for (int i = zeroIndex + 1; i < queue.size(); i++)
    {
        // Optimized version
        /*
            Normally it would be
            s2 -= v * (i + 1);
            s2 += v * (i);
        */
        s2 -= queue[i];
        ans = max(ans, s2);
    }

    s2 = s;
    for (int i = zeroIndex; i >= 0; i--)
    {
        s2 += queue[i];
        ans = max(ans, s2);
    }

    write(ans);


    _Exit(0);
}