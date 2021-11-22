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

    dread(int, n);
    vector<int> meals(n);
    vector<int> prefixMeals(n);
    int s = 0;
    rep(i, n)
    {
        dread(int, happiness);
        s += happiness;
        prefixMeals[i] = s;
        meals[i] = happiness;
    }

    int ans = -inf;

    ans = max(ans, meals[0]);
    ans = max(ans, meals[n-1]);

    vector<int> upqueries(n);
    int biggest = -inf;
    per(i,n-1)
    {
        biggest = max(biggest, prefixMeals[i]);
        upqueries[i] = biggest-prefixMeals[i];
    }


    vector<int> downqueries(n);
    int smallest = 0;
    for(int i = 0; i < n-1;i++)
    {
        smallest = min(smallest, prefixMeals[i]);
        if (i > 0)
        {

            downqueries[i] = prefixMeals[i-1] - smallest;
        }
    }


    for (int i = 1; i < n-1; i++)
    {
        int start = meals[i];
        int maxGuaranteed = min(downqueries[i], upqueries[i]);
        ans = max(ans, start + maxGuaranteed);

    }

    write(ans);


    _Exit(0);
}