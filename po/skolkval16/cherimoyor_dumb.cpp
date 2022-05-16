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

int valuesum(unordered_map<int, int>& m)
{
    int ret = 0;
    repe(v, m)
    {
        ret += v.second;
    }
    return ret;
}

int tryshit(vector<unordered_map<int, int>> sol, int n)
{
    vector<int> indices(n + 2);
    rep(i, n + 2)
    {
        indices[i] = i;
    }
    rep(i, n + 2)
    {
        swap(indices[i], indices[rand() % (n + -1)]);
    }
    rep(k, 1000)
    {
        repe(i, indices)
        {
            int s = valuesum(sol[i]);
            repe(v, sol[i])
            {
                if (v.second <= 0)
                {
                    break;
                }
                for (int j = v.first; j < v.first + 3; j++)
                {
                    if (valuesum(sol[j])+1 < s || (valuesum(sol[j]) < s && rand()/double(RAND_MAX) > 0.9))
                    {
                        v.second--;
                        sol[j][v.first]++;
                        if (v.second <= 0)
                        {
                            break;
                        }
                    }
                }

            }

        }
    }

    vector<int> v = { 0,10,19,27,34,40,45,49,52,54,55 };
    int ans = 0;
    repe(mapper, sol)
    {
        int d = 0;
        repe(v, mapper)
        {
            d += v.second;
        }
        d = min((int)v.size() - 1, d);
        ans += v[d];
    }

    return ans;
}



int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread(int, n);
    vector<int> days;
    rep(i, n)
    {
        readpush(int, days);
    }

    vector<unordered_map<int,int>> sol(n+2);
    per(i,n-1)
    {
        priority_queue<pair<int,int>> values;

        values.push({ -valuesum(sol[i+0]),i+0});
        values.push({ -valuesum(sol[i+1]),i+1 });
        values.push({ -valuesum(sol[i+2]),i+2 });

        int left = days[i];

        while (left > 0)
        {
            pair<int, int> top = values.top();
            values.pop();
            top.first--;
            if (!setcontains(sol[top.second],i))
            {
                sol[top.second][i] = 0;
            }
            sol[top.second][i]++;
            values.push(top);
            left--;
        }


    }



    int ans = -inf;

    auto Start = std::chrono::high_resolution_clock::now();

    while (true)
    {
        ans = max(ans, tryshit(sol, n));
        auto End = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> Elapsed = End - Start;
        if (Elapsed.count() >= 900)
            break;
    }


    write(ans);

    _Exit(0);
}