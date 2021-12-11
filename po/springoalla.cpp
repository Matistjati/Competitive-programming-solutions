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
#define vvi vector<vi>
#define vvvi vector<vvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vp3 vector<p3>
#if enablell
#define inf 1e18
#else
#define inf int(1e9)
#endif

#define read(a) cin >> a
#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
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
#define sz(container) ((int)container.size())

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

#define anstype tuple<int,int,vector<int>>


int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, n, t);

    vi memo(t + 40001, inf);
    vp2 trails(n*2);
    vp3 extraTrails(n*2);
    rep(i, n)
    {
        dread(int, trail);
        trails[i*2] = {trail,1};
        trails[i*2+1] = {trail + trail / 2,2};
        extraTrails[i*2] = {trail,1,i};
        extraTrails[i*2+1] = {trail + trail / 2,2,i};
    }

    memo[0] = 0;

    repp(i, 1, memo.size())
    {
        repe(j, trails)
        {
            if (i - j.first >= 0)
            {
                if (memo[i - j.first] + j.second < memo[i])
                {
                    memo[i] = memo[i - j.first] + j.second;
                }
            }
        }
    }

    repp(i, t, memo.size())
    {
        int p = memo[i];
        if (memo[i] != inf)
        {
            cout << i << " " << memo[i] << "\n";
        }
        else
        {
            continue;
        }

        vi runs(n);
        while (i > 0)
        {
            repe(j, extraTrails)
            {
                int time;
                int cost;
                int index;
                tie(time, cost, index) = j;
                if (i-time>=0&&memo[i-time] == p-cost)
                {
                    runs[index] += time;
                    p-=cost;
                    i -= time;
                    break;
                }
            }
        }
        repe(j, runs)
        {
            cout << j << " ";
        }
        break;
    }




    quit;
}