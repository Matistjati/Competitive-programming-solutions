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

pair<ll, int> howlong(vector< pair<ll, int>>& memo, ll N, char x[], ll pos, bool first, ll s)
{
    if (pos == N)
    {
        return { 0,pos};
    }

    pair<ll, int>& v = memo[(pos * 2) + first];

    if (v.first != -1)
    {
        ll sum = v.first;

        sum += (x[pos] == 'a') * (v.second - pos);

        return {sum,v.second};
    }

    if (pos > 0 && !first && x[pos-1] == x[pos] && x[pos] == 'a')
    {
        return { 0,pos };
    }

    s += x[pos] == 'a';

    pair<ll, int> r = howlong(memo, N, x, pos + 1, false, s);


    memo[(pos * 2) + first] = r;


    r.first += (x[pos] == 'a') * (r.second - pos);


    return r;
}

ll fibonacci(int N, char X[])
{
    ll ans = 0;
    vector< pair<ll, int>> memo(N*2, {-1,-1});
    rep(i, N)
    {
        ans += get<0>(howlong(memo, N, X, i, true, 0));
    }
    return ans;
}