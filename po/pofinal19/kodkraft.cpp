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

    dread2(ll, n, k);

    readvector(ll, contests, n);

    vector<vector<ll>> n_contests(k+1);

    rep(i, n)
    {
        n_contests[contests[i]].push_back(i);
    }

    vector<ll> smallest;
    ll n_smallest = inf;
    repe(contest, n_contests)
    {
        if (contest.size() && contest.size() < n_smallest)
        {
            n_smallest = contest.size();
            smallest = contest;
            if (n_smallest==1)
            {
                break;
            }
        }
    }

    ll ans = linf;

    repe(start, smallest)
    {
        ll curr = contests[start]-1;
        ll steps = 0;
        ll i = start;

        while (curr > 0)
        {
            auto it = lower_bound(all(n_contests[curr]), i);
            // Left side
            if (it != begin(n_contests[curr]))
            {
                it = prev(it);
                steps += i-*it;
                i = *it;
            }
            else
            {
                it = prev(end(n_contests[curr]));
                steps += n - *it + i;
                i = *it;
            }
            curr--;
            // Right side
        }


        curr = contests[start] + 1;
        i = start;
        while (curr <= k)
        {
            auto it = lower_bound(all(n_contests[curr]), i);
            // Right side
            if (it != end(n_contests[curr]))
            {
                steps += *it -i;
                i = *it;
            }
            else
            {
                it = begin(n_contests[curr]);
                steps += n-i+*it;
                i = *it;
            }
            curr++;
            // Right side
        }

        ans = min(ans, steps);
    }

    write(ans+1);

    cout << endl;
    _Exit(0);
}